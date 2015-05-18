#ifndef _MSC_VER

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/resource.h>
#include <string.h>
#include "subprocess.h"

static void sigchld(int sig, siginfo_t *siginfo, void *context) {
  mrb_hash_delete_key(
      g_mrb, mrb_gv_get(g_mrb, mrb_intern_cstr(g_mrb, SHELL_CHILD_LIST)),
      mrb_fixnum_value((mrb_int)siginfo->si_pid));
}

mrb_value mrb_s_fork(mrb_state *mrb, mrb_value *s_cmd, mrb_value *s_in,
                     mrb_value *s_out) {
  FILE *cmd;
  pid_t childID;
  // pid_t endID;
  // int exit_status = 0;

  if (NULL == g_mrb) {
    g_mrb = mrb;
  }

  if (-1 == (childID = fork())) { //Start a child process.
    perror("fork error");
    return (mrb_false_value());
  } else if (0 == childID) {      // This is the child.
    freopen(mrb_string_value_cstr(mrb, s_out), "w", stdout);
    cmd = popen(mrb_string_value_cstr(mrb, s_cmd), "w");
    fputs(mrb_string_value_cstr(mrb, s_in), cmd);
    fflush(cmd);
    pclose(cmd);
    exit(EXIT_SUCCESS);
  } else {                        // This is the parent.
    struct sigaction act;
    memset(&act, '\0', sizeof(act));
    act.sa_sigaction = &sigchld;
    act.sa_flags = SA_SIGINFO;
    mrb_hash_set(mrb, mrb_gv_get(mrb, mrb_intern_cstr(mrb, SHELL_CHILD_LIST)),
                 mrb_fixnum_value((mrb_int)childID), *s_cmd);
    if (sigaction(SIGCHLD, &act, NULL) < 0) {
      perror("sigaction");
      return mrb_false_value();
    }
    return mrb_fixnum_value(childID);
  }
}

#endif