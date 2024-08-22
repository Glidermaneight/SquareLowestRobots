#pragma once

typedef enum {
  Integer,
  Float,
  Double,
  Id,
  Equal,
  OpenParen,
  CloseParen,
  BinaryOp,
  Int,
  Char,
  String,
  Bool,
  DoubleType,
  FloatType,
  EOF
}TokenType;

typedef struct{
  char* value;
  void* next;
  void* prev;
  TokenType type;
}Token;

struct Keyword {
  const char* name;
  TokenType type;
};

Token* addToken(Token **headToken, const char* value, TokenType type);

int removeToken(Token** headToken, char* value);

Token* tokenize(char* sourceCode);