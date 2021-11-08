#include "../headers/includes.h"
#include "../headers/helpers.h"

void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void WRITE();
void READ();
void EXPR();
void COND();
void TERM();
void FACT();

void CONSTS(){
    switch(current_token){
        case CONST_TOKEN :
            next_token();
            test_symbol(ID_TOKEN, ERR);
            test_symbol(EQUAL_TOKEN, ERR);
            test_symbol(NUM_TOKEN, ERR);
            test_symbol(SC_TOKEN, ERR);
            while(current_token == ID_TOKEN){
                next_token();
                test_symbol(EQUAL_TOKEN, ERR);
                test_symbol(NUM_TOKEN, ERR);
                test_symbol(SC_TOKEN, ERR);
            }
            break;
        case BEGIN_TOKEN : break;
        case VAR_TOKEN : break;
        default : printf("ERROR CONSTS\n"); exit(EXIT_FAILURE);
    }
}

void VARS(){
    switch(current_token){
        case VAR_TOKEN :
            next_token();
            test_symbol(ID_TOKEN, ERR);
            while(current_token == COM_TOKEN){
                next_token();
                test_symbol(ID_TOKEN, ERR);
            }
            test_symbol(SC_TOKEN, ERR);
            break;
        case BEGIN_TOKEN : break;
        default : printf("ERROR VARS\n"); exit(EXIT_FAILURE);
    }
}

void INST(){

    switch (current_token) {
        case BEGIN_TOKEN :
            INSTS();
            break;
        case ID_TOKEN :
            AFFEC();
            break;
        case IF_TOKEN :
            SI();
            break;
        case WHILE_TOKEN :
            TANTQUE();
            break;
        case WRITE_TOKEN :
            WRITE();
            break;
        case READ_TOKEN :
            READ();
            break;
        case SC_TOKEN : break;
        case END_TOKEN : break;
        default:
            printf("ERROR INST\n");
            exit(EXIT_FAILURE);
    }

}

void READ() {
    test_symbol(READ_TOKEN, ERR);
    test_symbol(OP_TOKEN, ERR);
    test_symbol(ID_TOKEN, ERR);
    while( current_token == COM_TOKEN ){
        next_token();
        test_symbol(ID_TOKEN, ERR);
    }
    test_symbol(CP_TOKEN, ERR);
}

void WRITE() {
    test_symbol(WRITE_TOKEN, ERR);
    test_symbol(OP_TOKEN, ERR);
    EXPR();
    while( current_token == COM_TOKEN ){
        next_token();
        EXPR();
    }
    test_symbol(CP_TOKEN, ERR);

}

void TANTQUE() {
    test_symbol(WHILE_TOKEN, ERR);
    COND();
    test_symbol(DO_TOKEN, ERR);
    INST();
}

void SI() {
    test_symbol(IF_TOKEN, ERR);
    COND();
    test_symbol(THEN_TOKEN, ERR);
    INST();
}

int is_cond_operator(){
    return current_token == EQUAL_TOKEN || current_token == NOT_EQUAL_TOKEN || current_token == LOWER_TOKEN
    || current_token == GREATER_TOKEN || current_token == LOWER_OR_EQUAL_TOKEN || current_token == GREATER_OR_EQUAL_TOKEN;
}

int is_arith_operator(){
    return current_token == PLUS_TOKEN || current_token == MINUS_TOKEN || current_token == MULTI_TOKEN
    || current_token == DIV_TOKEN;
}

void COND() {
    EXPR();
    if (is_cond_operator()) {
        next_token();
        EXPR();
    }
    else{
        fprintf(stderr, "ERROR COND");
        exit(EXIT_FAILURE);
    }
}

void AFFEC() {
    test_symbol(ID_TOKEN, ERR);
    test_symbol(ASSIGN_TOKEN, ERR);
    EXPR();
}

void EXPR() {
    TERM();
    while(current_token == PLUS_TOKEN
    || current_token == MINUS_TOKEN){
        next_token();
        TERM();
    }
}

void TERM() {
    FACT();
    while(current_token == MULTI_TOKEN
          || current_token == DIV_TOKEN){
        next_token();
        FACT();
    }
}

void FACT() {
    switch (current_token) {
        case ID_TOKEN :
            next_token();
            break;
        case NUM_TOKEN:
            next_token();
            break;
        case OP_TOKEN:
            next_token();
            EXPR();
            test_symbol(CP_TOKEN, ERR);
            break;
        default :
            if( !is_cond_operator() ) {
                fprintf(stderr, "ERROR FACT %s", tokens[current_token]);
                exit(EXIT_FAILURE);
            }
    }



}

void INSTS(){
    test_symbol(BEGIN_TOKEN, ERR);
    INST();
    while( current_token == SC_TOKEN ){
        next_token();
        INST();
    }
    test_symbol(END_TOKEN, ERR);
}

void BLOCK(){
    CONSTS();
    VARS();
    INSTS();
}


void PROGRAM(){
    test_symbol(PROGRAM_TOKEN, ERR);
    test_symbol(ID_TOKEN, ERR);
    test_symbol(SC_TOKEN, ERR);
    BLOCK();
    test_symbol(PT_TOKEN, ERR);
}


void start_parser(){
    next_token();
    PROGRAM();

    if(current_token == EOF_TOKEN){
        printf("THE SOURCE CODE IS SYNTACTICALLY CORRECT");
    }else
        printf("ERROR : THERE IS A SYNTAX ERROR IN YOUR CODE");

}


