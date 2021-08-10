#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200

int main(int argc, char *argv[]) {
  int mark, pid;

  for (int i = LEFT; i < RIGHT; ++i) {
    if ((pid = fork()) < 0) {
      perror("fork()");
      exit(1);
    } else if (pid == 0) {
      mark = 1;
      for (int j = 2; j < i/2; ++j) {
        if (i % j == 0) {
          mark = 0;
          break;
        }
      }
      if (mark) {
        printf("%d is a primer\n", i);
      }
      exit(0);
    }

  }

  return 0;
}
