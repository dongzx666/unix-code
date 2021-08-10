#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELIMS " \t\n"

struct cmd_st {
  glob_t globres;
};

static void prompt(void) { printf("myshell-0.1$ "); }

static void parse(char *line, struct cmd_st *res) {
  char *tok;
  int i = 0;

  while (1) {
    tok = strsep(&line, DELIMS);
    if (tok == NULL) {
      break;
    }
    if (tok[0] == '\0') {
      continue;
    }
    glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &res->globres);
    i = 1;
  }
}

int main(int argc, char *argv[]) {

  char *line_buf = NULL;
  size_t line_buf_size = 0;
  struct cmd_st cmd;
  pid_t pid;

  while (1) {
    prompt();

    if (getline(&line_buf, &line_buf_size, stdin) < 0) {
      break;
    }

    parse(line_buf, &cmd);

    if (0) {
      // inner command
    } else {
      pid = fork();
      if (pid < 0) {
        perror("fork");
        exit(1);
      } else if (pid == 0) {
        execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
        perror("execvp");
        exit(1);
      } else {
        wait(NULL);
      }
    }
  }

  return 0;
}
