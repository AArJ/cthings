#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
  int c;
  char s[50];
  char o[50];
  char *args[5];
  args[0] = "/bin/as";
  args[2] = "-o";
  args[5] = NULL;
  if (argc == 1) {
    printf("Please specify a program\n");
    return 1;
  }

  for (int i = 1; i < argc; i++) {
    if ((strcmp(*(argv + i), "-o") == 0) && (i < (argc - 2))) {
      i += 2;
    }
    snprintf(s, 40, "%s.s", *(argv + i));
    snprintf(o, 40, "%s.o", *(argv + i));
    args[1] = s;
    args[3] = o;
    execv("/bin/as", args);
    printf("lol\n");
  }
 
  while ((c = getopt(argc, argv, "o:")) != -1) {
    if (c == 'o') {
      printf("%s\n", optarg);
    }
  }

  return 0;
}
