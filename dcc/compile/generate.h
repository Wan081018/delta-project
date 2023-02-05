#ifndef __GENERATE_H__

#define __GENERATE_H__

#include "../global.h"

errtype intermediate_code_generate(FILE *input, FILE *output);

int8_t *get_identifier(FILE *input, int32_t line);

uint8_t get_hex_number(FILE *input, int32_t line);

uint8_t get_num(int8_t ch);

#endif

