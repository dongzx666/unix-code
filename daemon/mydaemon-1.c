#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

#define FNAME "/tmp/out"

// /var/log/syslog

static int daemonize(void) {
  pid_t pid = fork();
  if (pid < 0) {
    return -1;
  } else if (pid > 0) {
    return 0;
  }
  int fd = open("/dev/null", O_RDWR);
  if (fd < 0) {
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
  openlog("mydaemon", LOG_PID, LOG_DAEMON);

  if (daemonize()) {
    syslog(LOG_ERR, "daemonize fail");
    exit(1);
  } else {
    syslog(LOG_INFO, "daemonize success");
  }

  fp = fopen(FNAME, "w");
  if (fp == NULL) {
    syslog(LOG_ERR, "fopen():%s", strerror(errno));
    exit(1);
  }
  syslog(LOG_INFO, "%s was open", FNAME);

  for (int i = 0;; i++) {
    fprintf(fp, "%d\n", i);
    fflush(fp);
    syslog(LOG_DEBUG, "%d is printed", i);
    sleep(1);
  }

  fclose(fp);
  closelog();

  return 0;
}
