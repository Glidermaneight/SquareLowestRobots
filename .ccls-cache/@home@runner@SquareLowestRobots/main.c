#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("running");
  char code[] = "int x = 5 * (5 + 5)";
  Token* iterator = tokenize(code);
  printf("\n%d\n", iterator == NULL);
  /*while (iterator != NULL) {
    printf("Value: %s ", iterator->value);
    printf("Data: %d\n", iterator->type);
    Token *temp = iterator;
    iterator = iterator->next;          // Move to the next token
    removeToken(&iterator, temp->value); // Remove the token from the list
  }*/
  parseForward(&iterator);
  return 0;
}
