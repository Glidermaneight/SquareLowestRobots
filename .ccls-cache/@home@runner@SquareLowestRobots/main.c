#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("running");
  char code[] = "int x = 5";
  parseAST(code);
  return 0;
}
