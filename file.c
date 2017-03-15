/*
  Deals with file access
  author: Gauthier
  creation date: 16, february 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "io.h"
#include "data.h"


/*
  Accesses source file and processes it
  @param program arguments, line value where program must be started
*/
void accessBasicProgram(char* argv[], int gotoValue) {
  // Opens input file
  FILE *basicFile;
  basicFile = fopen(argv[1], "r");

  // Sets whether goto is active or not
  int gotoAttained = 0;
  if (gotoValue == 0) {
    gotoAttained = 1;
  }

  char buff[255];  // Current line of the program
  char* firstWord = (char*) malloc(sizeof(buff));  // First word of current line
  int lineCode;  // Code of current line
  char* instruction = (char*) malloc(sizeof(buff));  // Instruction read from the current line
  char* rest = (char*) malloc(sizeof(buff));  // Rest of the line after code and instruction

  if (basicFile) {
    while (fgets(buff, 255, (FILE*)basicFile) > 0) {
      firstWord = strtok(buff, " ");

      if (strstr(firstWord,"REM") == NULL) {
        // Case current line is not a comment
        lineCode = atoi(firstWord);
        if (gotoValue == lineCode) {
          // Case goto line is attained
          gotoAttained = 1;
        }
        if (gotoAttained == 1) {
          // Action performed when goto line is marked as attained
          instruction = strtok(NULL," ");
          rest = strtok(NULL,"\0");
          if (instruction != NULL) {  // Prevents dealing with empty lines
            if (strstr(instruction,"PRINT") != NULL) {
              // Printing instruction
              basicPRINT(rest);
              printf("\n");
            } else if (strstr(instruction, "END") != NULL) {
              // End of file reached
              printf("%d variables\n", variableNumber);
              for (int i=0;i<variableNumber;i++) {
                printf("%s = %s\n", variablesNames[i], variablesValues[i]);
              }

              // Frees memory
              free(rest);

              // Exits
              fclose(basicFile);
              exit(0);
            } else if (strstr(instruction, "INPUT") != NULL) {
              // Query input from user
              basicINPUT(rest);
            } else if (strstr(instruction, "LET") != NULL) {
              // Defines new variable
              basicLET(rest);
            } else if (strstr(instruction, "GOTO") != NULL) {
              int gtVal = atoi(strtok(rest,"\n"));
              fclose(basicFile);

              // Frees memory
              free(firstWord);
              free(instruction);
              free(rest);

              // Calls program interpreting function again
              accessBasicProgram(argv, gtVal);

              // Exits interpreter
              exit(0);
            }
          }
        }
      }
    }
    fclose(basicFile);
  } else {
    // Prints error message if input file can't be accessed
    printf("File %s not found.\n", argv[1]);

    // Frees memory
    free(firstWord);
    free(instruction);
    free(rest);

    // Exits program with error
    fclose(basicFile);
    exit(1);
  }
}

/*
int basicGOTO(int value) {
  return
}
*/
