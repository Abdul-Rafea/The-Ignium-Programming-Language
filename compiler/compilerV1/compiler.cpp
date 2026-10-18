#include <fstream>
#include <iostream>

#include <vector>
#include <string>

#include "util/util.h"
#include "lexer/lexer.h"
#include "compiler.h"

// Functions Prototypes
void run(std::ifstream& file, CompilerContext& compilerContext);
void printTokens(const std::vector<Token>& tokens);
void printErrors(const std::vector<Error>& errors);

// Main Function
int main() {
    // Creating Compiler Context
    CompilerContext compilerContext;

    // Cli
    while(true) {
        std::string command;
        std::string filename;
        std::string directory = "src/";

        std::cout << "Enter Command: ";
        std::cin >> command >> filename;

        // Running The Command
        if(command == "run") {
            std::ifstream file(directory + filename);
            if(!file.is_open()) {
                Error error;
                error.severity = 0;
                error.type = "File Error";
                error.message = "Unable to open " + filename;

                compilerContext.errors.push_back(error);
            }

            std::cout << "Running " << filename << " ..........";
            run(file, compilerContext);
        }
        else {
            Error error;
            error.severity = 0;
            error.type = "Command Error";
            error.message = "The command you entered does not exist";

            compilerContext.errors.push_back(error);
        }

        // Printing Errors
        if(compilerContext.errors.size() > 0) {
            printErrors(compilerContext.errors);
        }

        // Cleanup
        compilerContext.errors.clear();
        compilerContext.tokens.clear();
    }
}

// Function Definitions
void run(std::ifstream& file, CompilerContext& compilerContext) {
    runLexer(file, compilerContext);
    printTokens(compilerContext.tokens);
}

void printErrors(const std::vector<Error>& errors) {
    std::cout << std::endl << errors.size() << " Errors Found: -" << std::endl;

    for(int i = 0; i < errors.size(); i++) {
        if(errors.at(i).severity == 0) {
            std::cout << RED;
        }
        else {
            std::cout << YELLOW;
        }
        std::cout << "  -> " << errors.at(i).type << " : " << errors.at(i).message << std::endl;
    }

    std::cout << RESET;
}

void printTokens(const std::vector<Token>& tokens) {
    std::cout << std::endl << tokens.size() << " Tokens Found: -" << std::endl;

    for(int i = 0; i < tokens.size(); i++) {
        std::cout << "  -> " << tokens.at(i).value << std::endl;
    }
}