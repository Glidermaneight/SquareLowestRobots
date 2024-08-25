#include "ast.h"
#include "lexer.h"
#pragma once

void parseForward(Token** tokens);
void parseBack(Token** tokens);
Node* createNode(Node** head, int type);
int parseAST(char* src);