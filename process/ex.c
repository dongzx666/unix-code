#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  puts("begin");

  fflush(NULL);

  execl("/bin/date", "date", "+%s", NULL);
  perror("execl");
  exit(1);

  puts("end");
  return 0;
}
