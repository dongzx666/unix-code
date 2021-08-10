#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FNAME "timelog.out"
#define BUFSIZE 1024


int main(int argc, char *argv[])
{
  char buf[BUFSIZE];
  int count = 0;
  time_t stamp;
  struct tm* tm;
  FILE* fp;
  fp = fopen(FNAME, "a+");
  if (fp == NULL) {
    perror("fopen()");
    exit(1);
  }

  while (fgets(buf, BUFSIZE, fp) != NULL) {
    count++;
  }
  

  while (1) {
    time(&stamp);
    tm = localtime(&stamp);
    fprintf(fp, "%-4d%d-%d-%d %d:%d:%d\n", ++count, \
	1900+tm->tm_year, 1+tm->tm_mon, tm->tm_mday, \
	tm->tm_hour, tm->tm_min, tm->tm_sec);
    fflush(fp);
    sleep(1);
  }

  fclose(fp);
  
  return 0;
}
