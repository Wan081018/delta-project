#include "compile.h"

errtype compile(FILE *input, FILE *output){
    if (grammar_analyse(input) == ERROR)
        return ERROR;
    fseek(input, 0, SEEK_SET);
    if (intermediate_code_generate(input, output) == ERROR)
        return ERROR;
    return NO_ERROR;
}
