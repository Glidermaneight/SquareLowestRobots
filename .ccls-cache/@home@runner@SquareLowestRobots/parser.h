#include "ast.h"
#include "lexer.h"
#pragma once

Token** parseForward(Token*** tokens);
void parseBack(Token*** tokens);