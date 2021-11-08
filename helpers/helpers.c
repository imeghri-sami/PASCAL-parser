#include "../headers/includes.h"
#include "../headers/global.h"
#include "../headers/tokens.h"
#include "../headers/errors.h"

int index_of(char* token_name){
    char** ptr = tokens;

    while(ptr){
        if( !strcmp(*ptr, token_name) ) return ptr - tokens;
        ptr++;
    }

    fprintf(stderr, "ERROR : token not found !");
    exit(EXIT_FAILURE);
}

void next_token(){
    char* token_name = malloc(20);
    fscanf(file_ptr, "%s\n", token_name);

    current_token = index_of(token_name);
}

void open_file(char* file_name){
    file_ptr = fopen(file_name, "r");

    if(file_ptr == NULL) {
        perror("Opening file ");
        exit(EXIT_FAILURE);
    }
}

void close_file(){
    fclose(file_ptr);
}

void test_symbol(enum token_enum token, error_enum err){
    if( current_token == token ){
        next_token();
    }else{
        fprintf(stderr, "%s (%s)\n", error_messages[err], tokens[token]);
        exit(EXIT_FAILURE);
    }
}
