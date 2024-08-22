#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
int findLength(Token* head) {
    int count = 0;
    for (Token* cur = head; cur != NULL; cur = cur -> next)
      count++;
    return count;
}

void parseForward(Token** tokens){
  Token* current = *tokens;
  while(current != NULL){
    printf("Value: %s ", current->value);
    printf("Data: %d\n", current->type);
    Token* temp = current;
    current = current->next;
  }
}

/*void parseBack(Token** tokens){
  Token* current = *tokens;
  printf("%d ", current == NULL);
  while(current != NULL){
    printf("Value: %s ", current->value);
    printf("Data: %d\n", current->type);
    Token* temp = current;
    current = current->prev;
    removeToken(&current, temp->value);
  }
}*/