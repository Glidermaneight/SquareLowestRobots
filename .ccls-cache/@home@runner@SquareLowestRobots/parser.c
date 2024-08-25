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

void parseBack(Token** tokens) {
  Token* current = *tokens;
  while (current && current->next != NULL) {
    current = current->next;
  }
  while (current != NULL) {
    printf("Value: %s ", current->value);
    printf("Data: %d\n", current->type);
    Token* temp = current;
    current = current->prev;
    removeToken(tokens, temp->value);
  }
}

Node* createNode(Node** head, int type){
  Node* newNode = malloc(sizeof(Token));
  newNode->type = type;
  newNode->next = NULL;
  if (*head == NULL) {
    newNode->prev = NULL;
    *head = newNode;
  } else {
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    printf("%d\n", temp == NULL);
  }
  return newNode;
}

int removeNode(Node** headNode, int type) {
  Node* current = *headNode;
  Node* prev = NULL;
  while (current != NULL) {
    if (current->type == type) {
      if (current == *headNode) {
        *headNode = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      return 1;
    }
    prev = current;
    current = current->next;
  }
  return 0;
}

Program buildAST(char* src){
  Token* tokens = tokenize(src);
  Program program = {NULL};
  Token* current = tokens;
  Token* eof = tokens;
  program.head->prev = (Node*)program.head->prev;
  program.head->next = (Node*)program.head->next;
  while(eof->next != NULL){
    eof = eof->next;
  }
  while(current != eof){
    switch(current->type){
      case Integer:
        {
          IntObject integer; 
          integer.extends = createNode(&program.head, IntNode);
          integer.value = atoi(current->value);
          break;
        }
      case FloatType:
        {
          FloatObject f_point;
          f_point.extends = createNode(&program.head, FloatNode);
          f_point.value = strtof(current->value, NULL);
          break;
        }
      case Char:
        {
          CharObject character;
          character.extends = createNode(&program.head, CharNode);
          character.value = *current->value;
          break;
        }
      case Double:
        {
          DoubleObject eight;
          eight.extends = createNode(&program.head, DoubleNode);
          eight.value = atof(current->value);
          break;
        }
      case Bool:
        {
          BoolObject boolean;
          boolean.extends = createNode(&program.head, BoolNode);
          if(*current->value == 0 || *current->value == 1){
            boolean.value = atoi(current->value);
          }
          break;
        }
      case String:
        {
          StringObject string;
          string.extends = createNode(&program.head, StringNode);
          string.value = current->value;
          break;
        }
      case BinaryOp:
        {
          BinaryOperator op;
          op.extends = createNode(&program.head, BinaryOperatorNode);
          op.value = current->value;
          break;
        }
      case Equal:
        {
          EqualType equal;
          equal.extends = createNode(&program.head, EqualNode);
          equal.value = '=';
          break;
        }
    }
    current = current->next;
  }
  printf("AST built\n");
  return program;
}

int parseAST(char* src){
  Program program = buildAST(src);
  
  Node* head = program.head;
   
  if(head == NULL){
    printf("head is null\n");
    exit(0);
  }
  else{
    Node* current = head;
    if(current == NULL){
      printf("current is null\n");
      exit(0);
    }
    while(current != NULL){
      current->prev = (Node*)current->prev;
      current->next = (Node*)current->next;
      Node* prev = current->prev;
      Node* next = current->next;
      switch(current->type){
        case EqualNode:
          {
            //if(current->prev != NULL && current->next != NULL){
              if(prev->type == IntNode && next->type == IntNode){
                IntObject* left = (IntObject*)current->prev;
                IntObject* right = (IntObject*)current->next;
                printf("setting integer with value %d to integer with value %d", left->value, right->value);  
                left->value = right->value;
              }
              else{
                printf("incompatible types");
                exit(0);
              }
              if(prev->type == FloatNode && next->type == IntNode || next->type == FloatNode){
                FloatObject* left = (FloatObject*)current->prev;
                FloatObject* right = (FloatObject*)current->next;
                printf("setting float with value %f to float with value %f", left->value, right->value);  
                left->value = right->value;
              }
              else{
                printf("incompatible types");
                exit(0);
              }
              if(prev->type == CharNode && next->type == CharNode){
                CharObject* left = (CharObject*)current->prev;
                CharObject* right = (CharObject*)current->next;
                printf("setting character with value %c to character with value %c", left->value, right->value);
                left->value = right->value;
              }
              else{
                printf("incompatible types");
                exit(0);
              }
              if(prev->type == StringNode && next->type == StringNode && next->type == CharNode){
                StringObject* left = (StringObject*)current->prev;
                StringObject* right = (StringObject*)current->next;
                printf("setting string with value %s to string with value %s", left->value, right->value);
                left->value = right->value;
              }
              else{
                printf("incompatible types");
                exit(0);
              }
            //}
            break;
          }
      }
      printf("AST parsed");
      removeNode(&head, current->type);
      current = current->next;
    }
  }
  return 1;
}