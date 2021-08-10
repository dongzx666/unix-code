#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <shadow.h>
#include <string.h>
#include <crypt.h>

int main(int argc, char *argv[])
{
  char* input_pass, *crypted_pass;
  struct spwd * shadow_line;


  if (argc < 2) {
    fprintf(stderr, "argc");
    exit(1);
  }

  input_pass = getpass("please input your password");

  shadow_line = getspnam(argv[1]);  

  crypted_pass = crypt(input_pass, shadow_line->sp_pwdp);
  
  if (strcmp(shadow_line->sp_pwdp, crypted_pass) == 0) {
    puts("OK");
  } else {
    puts("false");
  }

  return 0;
}
