#include "tokenizer.h"
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 300



// helper function to tokenize a boolean
Value *checkBool() {
    char boolean = (char)fgetc(stdin);
    Value *token = talloc(sizeof(Value));

    char next = (char)fgetc(stdin);
    if (next != EOF && next != ' ' && next != '\n' && next != '(' && next != ')') {
        printf("syntax error, expected delimeter\n");
        texit(1);
    }
    if (boolean == 'f'){
        token->i = 0;
        token->type = BOOL_TYPE;
    } else if (boolean == 't'){
        token->i = 1;
        token->type = BOOL_TYPE;
    } else {
        printf("Syntax error, expected boolean type\n");
        texit(1);
    }

    return token;
}


// handles ints and doubles as well as negative numbers, as well as the negative and postive symbol
Value *checkNumber(char charRead) {
    char value = charRead;
    Value *token = talloc(sizeof(Value));
    char *numArray = talloc(MAX_SIZE);
    numArray[0] = charRead;
    charRead = (char)fgetc(stdin);

    // checks if second char is a digit
    if (isdigit(charRead)) {
        //char numArray[MAX_SIZE] = {sign}; 
        int i = 2;
        numArray[1] = charRead; 
        charRead = (char)fgetc(stdin);

        // loops over the rest of the digits
        while (isdigit(charRead)) { 
            if (i < MAX_SIZE) {
                numArray[i] = charRead;
                i++;
            } else {
                printf("Syntax error: this number is too long\n");
                texit(1);
            }
            charRead = (char)fgetc(stdin);
        }
    
        // accounts for double types
        if (charRead == '.') {
            numArray[i] = charRead;
            i++;
            // same loop that goes over the rest of the digits
            charRead = (char)fgetc(stdin);
            while (isdigit(charRead)) { //loops over the rest of the digits
                if (i < MAX_SIZE) {
                    numArray[i] = charRead;
                    i++;
                } else {
                    printf("Syntax error: this number is too long\n");
                    texit(1);
                }
                charRead = (char)fgetc(stdin);
            }

            // checking that double ends in proper delimeter
            if (charRead != EOF && charRead != ' ' && charRead != '\n' && charRead != '(' && charRead != ')') {
                printf("syntax error: not a valid number\n");
                texit(1);
            }
            numArray[i] = '\0';
            // puts the last read character (not a digit) back into the file stream so no tokens are missed
            ungetc(charRead, stdin);
            // converts numArray to double
            token->d = atof(numArray);
            token->type = DOUBLE_TYPE;

        // if its just an int and not a double
        } else {
            numArray[i] = '\0';
            ungetc(charRead, stdin);
            // converts numArray to int
            token->i = atoi(numArray);
            token->type = INT_TYPE;
        }

    // if second char is a "."
    } else if (charRead == '.') {
        int j = 1;
        numArray[j] = charRead;
        j++;
        charRead = (char)fgetc(stdin);

        // same loop that goes over the rest of the digits
        while (isdigit(charRead)) { //loops over the rest of the digits
            if (j < MAX_SIZE) {
                numArray[j] = charRead;
                j++;
            } else {
                printf("Syntax error: this number is too long\n");
                texit(1);
            }
            charRead = (char)fgetc(stdin);
        }
        

        // checking that double ends in proper delimeter
        if (charRead != EOF && charRead != ' ' && charRead != '\n' && charRead != '(' && charRead != ')') {
            printf("syntax error: not a valid number\n");
            texit(1);
        }
        // puts the last read character (not a digit) back into the file stream so no tokens are missed
        numArray[j] = '\0';
        ungetc(charRead, stdin);
        // converts numArray to double
        token->d = atof(numArray);
        token->type = DOUBLE_TYPE;

    // if non a number and not a ".", checks for delimeters
    }  else if (charRead == EOF || charRead == ' ' || charRead == '\n' || charRead == '(' || charRead == ')') { // sign is a symbol
        ungetc(charRead, stdin);

        // if first (and only) char is a digit
        if (isdigit(numArray[0])) {
            numArray[1] = '\0';
            token->i = atoi(numArray);
            token->type = INT_TYPE;
        // else it has to be a + or - and a symbol
        } else {
            char *signSymbol = talloc(sizeof(char) * 2);
            signSymbol[0] = value;
            //char signSymbol[2] = {sign};
            signSymbol[1] = '\0';
            //token->s = talloc(2*sizeof(char));
            //strcpy(token->s, signSymbol);
            token->s = signSymbol;
            token->type = SYMBOL_TYPE;
        } 
    // if it doesn't fall in any of the above cases, syntax incorrect
    } else {
        printf("syntax error, not a number or symbol\n");
        texit(1);
    }


    return token;
}

// creates a token with OPEN_TYPE
Value *createOpenToken() {
    Value *token = talloc(sizeof(Value));
    token->type = OPEN_TYPE;

    return token;
}

// creates a token with CLOSE_TYPE
Value *createCloseToken() {
    Value *token = talloc(sizeof(Value));
    token->type = CLOSE_TYPE;

    return token;
}

// skips through comments
int skipComment(char charRead) {
    while (charRead != '\n' && charRead != EOF) {
        charRead = (char)fgetc(stdin);
    }
    if (charRead == EOF) {
        return 1;
    } else {
        return 0;
    }
}

// checks if string is valid and tokenizes string
Value *checkString(char charRead) {
    char *string = talloc(301);
    int i = 1;
    string[0] = '"';

    charRead = (char)fgetc(stdin);

    while (charRead != '"') {
        string[i] = charRead;
        i++;
        charRead = (char)fgetc(stdin);
    }
    string[i] = '"';
    string[i+1] = '\0';
    Value *token = talloc(sizeof(Value));
    token->type = STR_TYPE;
    token->s = string;

    return token;
}

// helper method to check whether charRead is a symbol
int inBNF(char charRead) {
    char symbolList[] = {'!' , '$' , '%' , '&' , '*' , '/' , ':' , '<' , '=' , '>' , '?' , '~' , '_', '^'};
    int flag = 0;
    for (int i = 0; i < 14; i++) {
        if (charRead == symbolList[i]) {
            return 1;
        } 
    }
    return 0;
    
}

// helper method to create symbol token if CharRead is deemed a symbol
Value *makeSymbolToken(char charRead) {
    Value *token = talloc(sizeof(Value));
    char *symbol = talloc(301);

    int i = 0;

    // while charRead is in our BNF and does not equal a delimeter
    while (charRead != EOF && charRead != ' ' && charRead != '\n' && charRead != '(' && charRead != ')' && (isalnum(charRead) || inBNF(charRead) || charRead == '.' || charRead == '+' || charRead == '-')) {  
        symbol[i] = charRead;
        i++;
        charRead = (char)fgetc(stdin);
    }
    // not part of the symbol so it adds charRead back into stream
    ungetc(charRead, stdin);
    symbol[i] = '\0';
    token->type = SYMBOL_TYPE;
    token->s = symbol;

    return token;

}





// Displays the contents of the linked list as tokens, with type information
void displayTokens(Value *list) {
    while (!isNull(list)) {
        switch (car(list)->type) {
        case OPENBRACKET_TYPE:
            break;
        case CLOSEBRACKET_TYPE:
            break;
        case DOT_TYPE:
            break;
        case SINGLEQUOTE_TYPE:
            break;
        case PTR_TYPE:
            break;
        case INT_TYPE:
            printf("%i:integer\n", car(list)->i);
            break;
        case DOUBLE_TYPE:
            printf("%lf:double\n", car(list)->d);
            break;
        case STR_TYPE:
            printf("%s:string\n", car(list)->s);
            break;
        case NULL_TYPE:
            break;
        case OPEN_TYPE:
            printf("(:open\n");
            break;
        case CLOSE_TYPE:
            printf("):close\n");
            break;
        case BOOL_TYPE:
            if (car(list)->i == 0) {
                printf("#f:boolean\n"); 
            } else {
                printf("#t:boolean\n");
            }
            break;
        case SYMBOL_TYPE:
            printf("%s:symbol\n", car(list)->s);
            break;
        case CONS_TYPE:
            break;
        }
        list = cdr(list);
    }
}


// Read all of the input from stdin, and return a linked list consisting of the
// tokens.
Value *tokenize() {
    Value *token_list = makeNull();
    char charRead = (char)fgetc(stdin);

    while (charRead != EOF) {
        if (charRead == '(') {
            token_list = cons(createOpenToken(), token_list);

        } else if (charRead == ')') {
            token_list = cons(createCloseToken(), token_list);

        // if there are spaces or new line
        } else if (charRead == ' ' || charRead == '\n') {
            charRead = (char)fgetc(stdin);
            continue;

        // Tokenizing a number, checks for sign first. 
        // (tokenizes negative sign and positive sign as a symbol if its by itself)
        } else if (isdigit(charRead) || charRead == '.' || charRead == '-' || charRead == '+') { 
            token_list = cons(checkNumber(charRead), token_list);

        // tokenizing a boolean
        } else if (charRead == '#') {
            token_list = cons(checkBool(), token_list);

        // ignoring a comment
        } else if (charRead == ';') {
            skipComment(charRead);

        // handles strings
        } else if (charRead == '"') {
            token_list = cons(checkString(charRead), token_list);

        // handles symbols
        } else if(isalpha(charRead) || inBNF(charRead)) {
            token_list = cons(makeSymbolToken(charRead), token_list);
        } else {
            printf("Syntax Error, there is something wrong with your input\n");
            texit(1);
        }
        charRead = (char)fgetc(stdin);
    }
    Value *revList = reverse(token_list);
  
    return revList;
}









