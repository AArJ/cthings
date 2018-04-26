#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
  int c;
  char output[500];
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
      char *utput = optarg;
      output = utput;
    }
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
      system("rm *.o");
      return 2;
    }
  }
 
  /*while ((c = getopt(argc, argv, "o:")) != -1) {
    if (c == 'o') {
      printf("%s\n", optarg);
    }
  }i*/
  printf("%s\n", output);
  return 0;
}
