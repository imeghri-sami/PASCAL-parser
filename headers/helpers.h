#ifndef PASCAL_PARSER_HELPERS_H
#define PASCAL_PARSER_HELPERS_H

#include "tokens.h"
#include "errors.h"

void open_file(char*);

void next_token();

void close_file();

void test_symbol(enum token_enum token, error_enum err);

#endif //PASCAL_PARSER_HELPERS_H
