#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
  int pid;

  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    execl("/bin/sh", "sh", "-c", "date +%s", NULL);
    perror("execl");
    exit(1);
  }

  wait(NULL);

  return 0;
}
