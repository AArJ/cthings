#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc == 4) {
    double coppermass = (double) *argv[1];
    double tempchangecop = (double) *argv[2];
    double tempchangesol = (double) *argv[3];
    double ccop = 0.385;
    double c = ((coppermass * tempchangecop * ccop) / (200.00 * tempchangesol));
    printf("%f\n", c);
    return 0;
  } else {
    printf("Please specify arguments:\nMass of Copper\nTemperature Change of Copper\nTemperature Change of Solution\n");
    return 1;
  }
}
