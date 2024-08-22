#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if a string consists only of alphabetic characters
static int isAlpha(const char *string) {
  while (*string) {
    if (!isalpha((unsigned char)*string)) {
      return 0;
    }
    string++;
  }
  return 1;
}

// Check if a string represents an integer
static int isInt(const char *src) {
  while (*src) {
    if (!isdigit((unsigned char)*src)) {
      return 0;
    }
    src++;
  }
  return 1;
}

// Check if a string is skippable (whitespace)
static int isSkippable(const char *str) {
  return (strcmp(str, " ") == 0 || strcmp(str, "\n") == 0 ||
          strcmp(str, "\t") == 0);
}

// Concatenate src to dest
void concatStr(char *dest, const char *src) { strcat(dest, src); }

// Shift the string by one character
static char shift(char **str) {
  char first = (*str)[0];
  memmove(*str, *str + 1, strlen(*str));
  return first;
}

// Add a new token to the token list
Token* addToken(Token** headToken, const char* value, TokenType type) {
  Token* newToken = malloc(sizeof(Token));
  newToken->value = strdup(value);
  newToken->type = type;
  newToken->next = *headToken;
  (*headToken)->prev = (Token*)(*headToken)->prev;
  (*headToken)->prev = newToken;
  *headToken = newToken;
  return newToken;
}

// Remove a token from the token list
int removeToken(Token **headToken, char *value) {
  Token *current = *headToken;
  Token *prev = NULL;

  while (current != NULL) {
    if (current->value == value) {
      if (current == *headToken) {
        *headToken = current->next;
      } else {
        prev->next = current->next;
      }
      free(current->value);
      free(current);
      return 1; // Successfully removed
    }
    prev = current;
    current = current->next;
  }

  return 0; // Not found
}

Token **tokenize(char *sourceCode) {
  Token *tokens = NULL;
  char *src = sourceCode;

  while (*src) {
    if (*src == '(') {
      addToken(&tokens, "(", OpenParen);
      src++;
    } else if (*src == ')') {
      addToken(&tokens, ")", CloseParen);
      src++;
    } else if (*src == '+' || *src == '-' || *src == '*' || *src == '/') {
      char op[2] = {*src, '\0'};
      addToken(&tokens, op, BinaryOp);
      src++;
    } else if (*src == '=') {
      addToken(&tokens, "=", Equal);
      src++;
    } else if (isdigit((unsigned char)*src)) {
      char num[256] = {0};
      size_t len = 0;
      while (isdigit((unsigned char)*src)) {
        num[len++] = *src++;
      }
      num[len] = '\0';
      addToken(&tokens, num, Integer);
    } else if (isalpha((unsigned char)*src)) {
      char ident[256] = {0};
      size_t len = 0;
      while (isalpha((unsigned char)*src)) {
        ident[len++] = *src++;
      }
      ident[len] = '\0';

      // Check if the identifier is a keyword
      static struct Keyword keywords[] = {
          {"int", Int},         {"char", Char}, {"double", DoubleType},
          {"float", FloatType}, {"bool", Bool}, {"string", String}};

      int recognized = 0;
      for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(ident, keywords[i].name) == 0) {
          addToken(&tokens, ident, keywords[i].type);
          recognized = 1;
          break;
        }
      }

      if (!recognized) {
        // Handle unrecognized identifiers if needed
      }
    } else if (isSkippable((char[]){*src, '\0'})) {
      src++;
    } else {
      printf("Unrecognized character found: %c\n", *src);
      src++;
    }
  }
  Token **ref_tokens = &tokens;
  addToken(&tokens, "End of File", EOF);
  return ref_tokens;
}
