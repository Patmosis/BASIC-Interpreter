/*
  Deals with input/output of the BASIC language
  author: Gauthier
  creation date: 16, february 2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "data.h"


/*
  Prints texts
*/
void basicPRINT(char* string) {
  // Copies string to avoid modifying it
  char* printed = (char*) malloc(sizeof(string)); ;
  strcpy(printed, string);

  // Next lines suppress quote marks in new string "printed"
  char* end = strrchr(printed,'\"');
  int len = strlen(printed)-strlen(end);
  printed[strlen(printed)-strlen(end)] = '\0';
  printed = strtok(printed, "\"");

  // Finally prints string
  printf("%s", printed);

  // TODO deal with string containing expressions
}

/*
  Prompt user to enter a string
*/
void basicINPUT(char* string) {
  // Obtains query prompt to be printed and print it
  char* query = strtok(string, ";");
  char* varName = strtok(NULL, "$");
  basicPRINT(query);

  // Actually queries input from user
  char input[255];
  fgets(input, sizeof(input), stdin);
  char* end = strrchr(input,'\n');
  end[0] = '\0';

  varName[strlen(varName)] = '\0';

  // Saves user input
  variablesNames[variableNumber] = (char*) malloc(sizeof(varName));
  variablesValues[variableNumber] = (char*) malloc(sizeof(input));
  strcpy(variablesNames[variableNumber], varName);
  strcpy(variablesValues[variableNumber], input);
  variableNumber++;
}
