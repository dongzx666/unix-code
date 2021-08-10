#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char *argv[])
{

  pid_t pid;
  printf("[%d]Begin\n",getpid());

  fflush(NULL);
  
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  } else if (pid == 0) {
    printf("[%d]child is working\n", getpid());
  } else {
    printf("[%d]parent is working\n", getpid());
  }

  printf("[%d]End\n",getpid());
  return 0;
}
