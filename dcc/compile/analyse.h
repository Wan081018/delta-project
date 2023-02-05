#ifndef __ANALYSE_H__

#define __ANALYSE_H__

#include "../global.h"

errtype grammar_analyse(FILE *input);

errtype match_identifier(FILE *input, int32_t line);

errtype match_hex_number(FILE *input, int32_t line);

#endif
 
