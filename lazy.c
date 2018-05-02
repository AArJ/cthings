#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//TODO: Get all errors to remove object files
int main(int argc, char **argv) {
  int c = argc - 3;
  int argn;
  char *point;
  char *output;
  //char s[500];
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
  argn = argc + 1;
  if (c != 0) {
    output = *(argv + 1);
    argn = argc + 3;
  }
  for (int i = 1; i < argc; i++) {
    if ((strcmp(*(argv + i), "-o") == 0)) {
      i += 2;
    }
    if (i >= argc) {
      break;
    }
    int check;
    int size;
    size = snprintf(NULL, 0, "as %s.s -o %s.o", argv[i], argv[i]);
    if (size < 0) {
      printf("Something really went wrong\n");
      return 1;
    }
    point = malloc(++size);
    if (point == NULL) {
      printf("Something really went wrong\n");
      return 1;
    }
    check = snprintf(point, size, "as %s.s -o %s.o", argv[i], argv[i]);
    if (check < 0) {
      printf("Something really went wrong\n");
      return 1;
    }
    //Start the assembly
    if (system(point) != 0) {
      printf("Something went wrong with assembly\n");
      free(point);
      system("rm *.o &> /dev/null");
      return 2;
    } 
    free(point);
  }
  int check;
  int size;
  char *args[argn];
  args[0] = "/usr/bin/ld";
  for (int i = 1; i < argc; i++) {
    if ((strcmp(*(argv + i), "-o") == 0)) {
      i += 2;
    }
    if (i >= argc) {
      break;
    }
    size = snprintf(NULL, 0, "%s.o", argv[i]);
    if (size < 0) {
      printf("Something really went wrong\n");
      return 1;
    }
    args[i] = malloc(++size);
    if (args[i] == NULL) {
      printf("Something really went wrong\n");
      return 1;
    }
    check = snprintf(args[i], size, "%s.o", argv[i]);
    if (check < 0) {
      printf("Something really went wrong\n");
      return 1;
    }
  }
  args[argn - 3] = "-o";
  args[argn - 2] = output;
  args[argn - 1] = NULL;
  pid_t proc;
  proc = fork();
  if (proc < 0) {
    printf("Something really went wrong\n");
    return 1;
  } else if (proc == 0) {
    if (execv("/usr/bin/ld", args)) {
      printf("errno: %i\n", errno);  
    }
    exit(1);
  } else {
    wait(NULL);
  }
  for (int i = 1; i < (argn - 3); i++) {
    free(args[i]);
  }
  system("rm *.o &> /dev/null");
  return 0;
}
