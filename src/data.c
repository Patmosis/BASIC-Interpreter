/*
  Deals with program data
  author: Gauthier
  creation date: 16, february 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"


/*
  Defines a variable
*/
void basicLET(char* string) {
  // Gets variable name
  char* varName = strtok(string," ");
  varName[strlen(varName)] = '\0';
  for (int i=0;i<variableNumber;i++) {
    if (strcmp(varName,variablesNames[i]) == 0) {
      // Error message when second declaration of a variable is found
      printf("ERROR: Variable %s is already defined.\n", varName);
      exit(1);
    }
  }

  // Not consider '='
  strtok(NULL," ");

  // Gets variable value
  char* varValue = strtok(NULL,"\0");

  char* end = (char*)malloc(sizeof(varValue));
  // Removes quote marks in case of a string
  if ((end = strrchr(varValue,'\"'))) {
    int len = strlen(varValue)-strlen(end);
    varValue[len] = '\0';
    varValue = strtok(varValue, "\"");
  }
  // Replaces \n bu \0
  char* endValue = strrchr(varValue, '\n');
  endValue[0] = '\0';

  // Adds new variable and its value to the list
  variablesNames[variableNumber] = (char*) malloc(sizeof(varName));
  variablesValues[variableNumber] = (char*) malloc(sizeof(varValue));
  strcpy(variablesNames[variableNumber], varName);
  strcpy(variablesValues[variableNumber], varValue);
  variableNumber++;

  // Frees memory
  free(end);
}
