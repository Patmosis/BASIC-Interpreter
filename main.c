/*
  BASIC interpreter
  author: Gauthier
  creation date: 16, february 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "file.h"
#include "data.h"


int variableNumber = 0;
char* variablesNames[255];
char* variablesValues[255];


int main(int argc, char* argv[]) {
  // Checks number of parameters
  if (argc == 1) {
    printf("No input argument.\n");
    printf("Use: ./basic basicFile\n");
    return 1;
  } else if (argc > 2) {
    printf("Too many arguments.\n");
    printf("Use: ./basic basicFile\n");
    return 1;
  }

  accessBasicProgram(argv, 0);

  // Frees memory
  for (int i=0;i<variableNumber;i++) {
    free(variablesNames[i]);
    free(variablesValues[i]);
  }

  printf("WARNING: You must end you BASIC program with END.\n");
  return 1;
}
