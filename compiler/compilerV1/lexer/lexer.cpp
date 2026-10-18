#include <fstream>
#include <iostream>

#include <string>
#include <vector>

#include "lexer.h"
#include "../compiler.h"

void runLexer(std::ifstream& file, CompilerContext& compilerContext) {
    char letter;
    Token token;

    while (file.get(letter)) {
        if (letter == ' ' || letter == '\n' || letter == '\t') {
            if(token.value.length() > 0) {
                compilerContext.tokens.push_back(token);
                token.value.clear();
            }
            continue;
        }
        else if (letter == ';') {
            compilerContext.tokens.push_back(token); // first push token
            token.value = ";";
            compilerContext.tokens.push_back(token); // then push semicolon
            token.value.clear();
            continue;
        }
        
        token.value.push_back(letter);
    }

    // End Of File Cleanup
    if(token.value.length() > 0) {
        compilerContext.tokens.push_back(token);
    }
}