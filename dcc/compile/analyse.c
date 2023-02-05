#include "analyse.h"
#include "../error/error.h"

errtype grammar_analyse(FILE *input){
	int8_t ch = fgetc(input);
	
	int32_t line = 1, bracket = 0;
	
	while (!feof(input)){
		switch (ch){
			case '.':
				if (match_identifier(input, line) == ERROR)
					return ERROR;
				break;
			
			case '0':
				if (match_hex_number(input, line) == ERROR)
					return ERROR;
				break;
			
			case '(':
				++ bracket;
				break;
			
			case ')':
				if (bracket == 0){
					put_error(ERROR, line, -1, "Unmatched round brackets.");
					return ERROR;
				}
				-- bracket;
				break;
			
			case '\n':
				++ line;
				break;
			
			case ',' :
			case ';' :
				break;
			
			default:
				if (isspace(ch))
					break;
				
				put_error(ERROR, line, -1, "Invalid character \'%c\' (&%x).", ch, ch);
				return ERROR;
			
		} 
		
		ch = fgetc(input);
		
	}
	
	if (bracket != 0){
		put_error(ERROR, line, -1, "Unmatched round brackets.");
		return ERROR;
	}
	
	return NO_ERROR;
	
} 

errtype match_identifier(FILE *input, int32_t line){
	int8_t ch = fgetc(input);
	
	ch = fgetc(input);
	
	while (!feof(input)){
		switch (ch){
			case '.':
			case '(':
			case ')':
			case '\n':
				fseek(input, -1, SEEK_CUR);
				return NO_ERROR;
			
			case ',' :
			case ';' :
				return NO_ERROR;
			
			default:
				if (isspace(ch))
					return NO_ERROR;
				if ('!'>ch || ch>'~'){
					put_error(ERROR, line, -1, "Invalid character \'%c\' (&%x) for an identifier.", ch, ch);
					return ERROR;
				}
				break;
			
		}
		
		ch = fgetc(input);
		
	}
	
	return NO_ERROR;
	
}

errtype match_hex_number(FILE *input, int32_t line){
	int8_t ch = fgetc(input);
	
	if (ch != 'x'){
		put_error(ERROR, line, -1, "Invalid beginning character \'%c\' (&%x) for an hexadecimal number (should be \'x\').", ch, ch);
		return ERROR;
	}
	
	ch = fgetc(input);
	
	while (!feof(input)){
		switch (ch){
			case '.':
			case '(':
			case ')':
			case '\n':
				fseek(input, -1, SEEK_CUR);
				return NO_ERROR;
			
			case ',' :
			case ';' :
				return NO_ERROR;
			
			default:
				if (isspace(ch))
					return NO_ERROR;
				if (!isxdigit(ch)){
					put_error(ERROR, line, -1, "Invalid character \'%c\' (&%x) for an hexadecimal number (should be \'0\'-\'9\', \'a\'-\'b\' or \'A\'-\'B\').", ch, ch);
					return ERROR;
				}
				break;
			
		}
		
		ch = fgetc(input);
		
	}
	
	return NO_ERROR;
	
}

