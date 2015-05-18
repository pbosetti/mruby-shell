
#ifndef MRUBY_SHELL_SUBPROCESS_H
#define MRUBY_SHELL_SUBPROCESS_H
#define SHELL_CHILD_LIST "$&"

#include <mruby.h>
#include <mruby/string.h>
#include <mruby/variable.h>
#include <mruby/hash.h>
#include <mruby/array.h>

static mrb_state *g_mrb = NULL;

mrb_value mrb_s_fork(mrb_state *mrb, mrb_value *s_cmd, mrb_value *s_in, mrb_value *s_out);

#endif