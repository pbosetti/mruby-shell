#include <mruby.h>

#if defined(_WIN32) || defined(_WIN64)
  #include <stdio.h>
  #define popen _popen
  #define pclose _pclose
  #define DEVNULL "nul"
#else
  #define DEVNULL "/dev/null"
#endif

#include "subprocess.h"

static mrb_value mrb_s_popen(mrb_state *mrb, mrb_value *s_cmd) {
  mrb_value s_out = mrb_str_new_cstr(mrb, "");
  mrb_value a_result = mrb_ary_new(mrb);
  FILE *cmd;
  char line[80];
  int exit_status = 0;

  cmd = popen(mrb_string_value_cstr(mrb, s_cmd), "r");
  while (fgets(line, 80, cmd) != NULL) {
    mrb_str_concat(mrb, s_out, mrb_str_new_cstr(mrb, line));
  }
  exit_status = pclose(cmd);
  mrb_ary_push(mrb, a_result, s_out);
  mrb_ary_push(mrb, a_result, mrb_fixnum_value(exit_status));
  return a_result;
}


static mrb_value mrb_async_call(mrb_state *mrb, mrb_value self) {
  mrb_value s_cmd;
  mrb_value s_in  = mrb_str_new_cstr(mrb, ""); 
  mrb_value s_out = mrb_str_new_cstr(mrb, DEVNULL);
  mrb_value a_result = mrb_ary_new(mrb);
  mrb_int n_arg = 0;

  n_arg = mrb_get_args(mrb, "S|SS", &s_cmd, &s_in, &s_out);
  a_result = mrb_s_fork(mrb, &s_cmd, &s_in, &s_out);

  return a_result;
}

static mrb_value mrb_shell_call(mrb_state *mrb, mrb_value self) {
  mrb_value s_cmd;
  mrb_value a_result = mrb_ary_new(mrb);
  mrb_int n_arg = 0;

  n_arg = mrb_get_args(mrb, "S", &s_cmd);
  a_result = mrb_s_popen(mrb, &s_cmd);

  return a_result;
}

void mrb_mruby_shell_gem_init(mrb_state *mrb) {
  mrb_define_method(mrb, mrb->kernel_module, "shell", mrb_shell_call,
                    MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb->kernel_module, "async", mrb_async_call,
                    MRB_ARGS_ARG(1,2));
  mrb_gv_set(mrb, mrb_intern_lit(mrb, SHELL_CHILD_LIST), mrb_hash_new(mrb));
  
#if defined(_WIN32) || defined(_WIN64)
  mrb_define_const(mrb, mrb->kernel_module, "RUBY_PLATFORM",
                   mrb_str_new_cstr(mrb, "mswin"));
#elif defined(__APPLE__)
  mrb_define_const(mrb, mrb->kernel_module, "RUBY_PLATFORM",
                   mrb_str_new_cstr(mrb, "darwin"));
#else
  mrb_define_const(mrb, mrb->kernel_module, "RUBY_PLATFORM",
                   mrb_str_new_cstr(mrb, "linux"));
#endif
}

void mrb_mruby_shell_gem_final(mrb_state *mrb) {}
