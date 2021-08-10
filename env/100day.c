#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
  time_t stamp;
  struct tm* tm;
  char timestr[BUFSIZE];

  stamp = time(NULL);
  tm = localtime(&stamp);
  strftime(timestr, BUFSIZE, "Now: %Y-%m-%d", tm);
  puts(timestr);

  tm->tm_mday += 100;
  (void)mktime(tm);
  strftime(timestr, BUFSIZE, "100days later:%Y-%m-%d", tm);
  puts(timestr);

  return 0;
}
