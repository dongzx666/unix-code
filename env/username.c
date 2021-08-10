#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
int main(int argc, char *argv[])
{
  struct passwd * pwdline;

  if (argc < 2) {
    fprintf(stderr, "Usage\n"); 
  } 

  pwdline = getpwuid(atoi(argv[1]));
  
  puts(pwdline->pw_name);
  
  return 0;
 
  
}
