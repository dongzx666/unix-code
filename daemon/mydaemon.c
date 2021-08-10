#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FNAME "/tmp/out"

static int daemonize(void) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return -1;
  } else if (pid > 0) {
    return 0;
  }
  int fd = open("/dev/null", O_RDWR);
  if (fd < 0) {
    perror("open");
    return -1;
  }
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);
  if (fd > 2) {
    close(fd);
  }

  setsid();
  chdir("/");
  // umask(0);
  return 0;
}

int main(int argc, char *argv[]) {
  FILE *fp;
  if (daemonize()) {
    exit(1);
  }

  fp = fopen(FNAME, "w");
  if (fp == NULL) {
    perror("fopen()");
    exit(1);
  }

  for (int i = 0;; i++) {
    fprintf(fp, "%d\n", i);
    fflush(fp);
    sleep(1);
  }

  return 0;
}
