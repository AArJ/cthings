#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
  int c = argc - 3;
  int argn;
  char *output;
  char s[500];
  if (argc == 1) {
    printf("Please specify a program\n");
    return 1;
  }
  while ((c = getopt(argc, argv, "o:h")) != -1) {
    if (c == 'h') {
      printf("help\n");
      return 0;
    }
    if (c == 'o') {
      output = optarg;
      c = 0;
      break;
    }
  }
  argn = argc;
  if (c != 0) {
    output = *(argv + 1);
    argn = argc + 2;
  }
  for (int i = 1; i < argc; i++) {
    if ((strcmp(*(argv + i), "-o") == 0)) {
      i += 2;
    }
    if (i >= argc) {
      break;
    }
    snprintf(s, 490, "as %s.s -o %s.o", *(argv + i), *(argv + i));
    if (system(s) != 0) {
      printf("Something went wrong with assembly\n");
      system("rm *.o &> /dev/null");
      return 2;
    }
  }
  printf("%s\n", output);
  char *args[argn];
  args[0] = "/bin/ld";
  for (int i = 1; i < (argn - 1); i++) {
    args[i] = *(argv + i);
  }
  args[argn - 2] = "-o";
  args[argn - 1] = output;
  for (int i = 0; i < argn; i++) {
    printf("%s\n", args[i]);
  }
  return 0;
}
