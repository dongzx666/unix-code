#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define BUFSIZE 1024
#define FMTSTRSIZE 1024
/*
 *  -y: year
 *  -m: month
 *  -d: day
 *  -H: hour
 *  -M: minute
 *  -S: second
 *
 * */
int main(int argc, char *argv[]) {
  time_t stamp;
  struct tm* tm;
  char timestr[BUFSIZE], fmtstr[FMTSTRSIZE];
  int c;
  FILE* fp = stdout;

  fmtstr[0] = '\0';
  stamp = time(NULL);
  tm = localtime(&stamp);

  while ((c = getopt(argc, argv, "-y:mdH:MS")) != -1) {
    switch (c) {
      case 1:
        if (fp == stdout) {
          fp = fopen(argv[optind-1], "w");
          if (fp == NULL) {
            perror("fopen");
            fp = stdout;
          }
        }
        break;
      case 'H':
        if (strcmp(optarg, "12") == 0) {
          strcat(fmtstr, "%I(%P) ");
        } else if (strcmp(optarg, "24") == 0) {
          strcat(fmtstr, "%H ");
        } else {
          fprintf(stderr, "Invalid argument");
        }
        break;
      case 'M':
        strcat(fmtstr, "%M ");
        break;
      case 'S':
        strcat(fmtstr, "%S ");
        break;
      case 'y':
        if (strcmp(optarg, "2") == 0) {
          strcat(fmtstr, "%y ");
        } else if (strcmp(optarg, "4") == 0) {
          strcat(fmtstr, "%Y ");
        } else {
          fprintf(stderr, "Invalid");
        }
        break;
      case 'm':
        strcat(fmtstr, "%m ");
        break;
      case 'd':
        strcat(fmtstr, "%d ");
        break;
      default:
        break;
    }
  }

  strcat(fmtstr, "\n");
  strftime(timestr, BUFSIZE, fmtstr, tm);
  fputs(timestr, fp);

  if (fp != stdout) {
    fclose(fp);
  }

  return 0;
}
