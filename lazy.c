#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
  int c = argc - 3;
  int argn;
  char *output;
  char s[500];
  char *ss[argc];
  for (int i = 0; i < argc; i++) {
    char asdf[50];
    ss[i] = asdf;
  }
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
  int check;
  int size;
  char *args[argn];
  args[0] = "/bin/ld";
  for (int i = 1; i < argc; i++) {
    if ((strcmp(*(argv + i), "-o") == 0)) {
      i += 2;
    }
    if (i >= argc) {
      break;
    }
    size = snprintf(NULL, 0, "as %s.s -o %s.o", argv[i], argv[i]);
    if (size < 0) {
      printf("Something really went wrong (snprintf)\n");
      return 1;
    }
    args[i] = malloc(++size);
    if (args[i] == NULL) {
      printf("Something really went wrong (malloc)\n");
      return 1;
    }
    check = snprintf(args[i], size, "%s.o", argv[i]);
    if (check < 0) {
      printf("Something really went wrong (2nd snprintf)\n");
    }
    printf("%i: %i\n", i, size);
  }
  args[argn - 2] = "-o";
  args[argn - 1] = output;
  for (int i = 0; i < argn; i++) {
    printf("args[%i]: %s\n", i, args[i]);
  }
  return 0;
}

