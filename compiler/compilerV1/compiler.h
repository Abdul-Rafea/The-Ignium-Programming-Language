#pragma once

#include <vector>
#include <string>

// Structures
struct Token {
    std::string value;
};

struct Error {
    bool severity;
    std::string type;
    std::string message;
};

struct CompilerContext {
    std::vector<Error> errors;
    std::vector<Token> tokens;
};
