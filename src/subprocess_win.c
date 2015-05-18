/* 
  Windows version
  See
https://msdn.microsoft.com/en-us/library/windows/desktop/ms682499(v=vs.85).aspx
*/
#ifdef _MSC_VER

#include "subprocess.h"

mrb_value mrb_s_fork(mrb_state *mrb, mrb_value *s_cmd, mrb_value *s_in, mrb_value *s_out) {
  FILE *cmd;
  int exit_status = 0;
  mrb_p(mrb, mrb_str_new_cstr(mrb, "****"));
  //freopen(mrb_string_value_cstr(mrb, s_out), "w", stdout);
  cmd = popen(mrb_string_value_cstr(mrb, s_cmd), "w");
  fputs(mrb_string_value_cstr(mrb, s_in), cmd);
  fflush(cmd);
  pclose(cmd);
  exit_status = pclose(cmd);
  return mrb_fixnum_value(exit_status);
}

#endif