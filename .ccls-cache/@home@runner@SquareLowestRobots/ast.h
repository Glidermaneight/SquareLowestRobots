#pragma once
typedef enum{
  ProgramNode,
  StringNode,
  CharNode,
  IntNode,
  FloatNode,
  DoubleNode,
  BoolNode,
  DeclarationNode,
  AssignmentNode,
  ExpressionNode,
  BinaryOperatorNode,
  IdentifierNode,
  EqualNode,
  EqualsNode
}NodeType;

typedef struct{
  void* prev;
  void* next;
  NodeType type;
}Node;

typedef struct{
  Node* head;
}Program;

typedef struct{
  Node* extends;
  char* value;
}StringObject;

typedef struct{
  Node* extends;
  char value;
}CharObject;

typedef struct{
  Node* extends;
  int value;
}IntObject;

typedef struct{
  Node* extends;
  float value;
}FloatObject;

typedef struct{
  Node* extends;
  double value;
}DoubleObject;

typedef struct{
  Node* extends;
  int value;
}BoolObject;

typedef struct{
  Node* extends;
  char* value;
}Declaration;

typedef struct{
  Node* extends;
  char* value;
}Assignment;

typedef struct{
  Node* extends;
  char* value;
}Expression;

typedef struct{
  Node* extends;
  char* value;
}BinaryOperator;

typedef struct{
  Node* extends;
  char* value;
}Identifier;

typedef struct{
  Node* extends;
  char value;
}EqualType;