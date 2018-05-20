#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//TODO: Get all errors to remove object files
int main(int argc, char **argv) {
  int c;
  int argn = argc + 1;
  char *point;
  char *output;
  int size; 
  int check;
  if (argc == 1) {
    printf("Please specify a program\n");
    return 1;
  }
  while ((c = getopt(argc, argv, "d:o:h")) != -1) {
    if (c == 'h') {
      printf("help\n");
      return 0;
    } else if (c == 'o') {
      output = optarg;
    } 
  }
  if (strcmp(output, "") == 0) {
    output = *(argv + 1);
    argn = argc + 3;
  }
  for (int i = 1; i < argc; i++) {
    //Make a string for the assembler
    if ((strcmp(*(argv + i), "-o") == 0)) {
      i += 2;
    }
    if (i >= argc) {
      break;
    }
    if ((strcmp(*(argv + i), "-d") == 0)) {
      i++;
    }
    if (i >= argc) {
      break;
    }
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

  //Fill the array
  char *args[argn];
  int index = 1;
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
    args[index] = malloc(++size);
    if (args[index] == NULL) {
      printf("Something really went wrong\n");
      return 1;
    }
    if (snprintf(args[index], size, "%s.o", argv[i]) < 0) {
      printf("Something really went wrong\n");
      return 1;
    }
    index++;
  }
  args[argn - 3] = "-o";
  args[argn - 2] = output;
  args[argn - 1] = NULL;
  
  //Link it
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
