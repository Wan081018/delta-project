#include "generate.h"
#include "../error/error.h"

errtype intermediate_code_generate(FILE *input, FILE *output){
	int8_t ch = fgetc(input);
	
	int32_t line = 1, in_arg = 0;
	
	fprintf(output, "push\n");
	fprintf(output, "mov *cur_back %%-%x\n", 1);
	
	while (!feof(input)){
		int8_t *idfy;
		uint8_t num;

		switch (ch){
			case '.':
				idfy = get_identifier(input, line);
				if (idfy == NULL)
					return ERROR;
				fprintf(output, "mov *%s_back .%s\n", in_arg!=0 ? "arg" : "cur", idfy);
				free(idfy);
				break;
			
			case '0':
				fgetc(input);
				num  = get_hex_number(input);
				fprintf(output, "mov *%s_back %%%x\n", in_arg!=0 ? "arg" : "cur", num);
				break;
			
			case '(':
				++ in_arg;
				fprintf(output, "push\n");
				break;
			
			case ')':
				fprintf(output, "call *lst_%s_back\n", in_arg!=0 ? "arg" : "cur");
				fprintf(output, "mov *lst_%s_back *cur_back\n", in_arg!=0 ? "arg" : "cur");
				fprintf(output, "pop\n");
				-- in_arg;
				break;
			
			case ',':
				fprintf(output, "inc %s_back\n", in_arg!=0 ? "arg" : "cur");
				fprintf(output, "mov *%s_back %%-%x\n", in_arg!=0 ? "arg" : "cur", -1);
				break;
			
			case ';':
				fprintf(output, "mov %s_back %s_front\n", in_arg!=0 ? "arg" : "cur", in_arg!=0 ? "arg" : "cur");
				break;
			
			case '\n':
				++ line;
				break;
			
		}
		
		ch = fgetc(input);
		
	}
	
	return NO_ERROR;
	
}

int8_t *get_identifier(FILE *input, int32_t line){
	int8_t *idfy = (int8_t *) malloc(sizeof(int8_t) * 256),
	        ch = fgetc(input);
	
	memset(idfy, 0, sizeof(idfy));
	
	int32_t len = 0;
	
	while (!feof(input)){
		switch (ch){
			case '.':
			case ',':
			case ';':
			case '(':
			case ')':
			case '\n':
				fseek(input, -1, SEEK_CUR);
				return idfy;
			
			default:
				if (isspace(ch))
					return idfy;
				idfy[len++] = ch;
				if (len == 256){
					put_error(ERROR, line, -1, "Too long identifier (should < 255).");
					free(idfy);
					return NULL;
				}
				break;
			
		}

		ch = fgetc(input);

	}

	return idfy;

}

uint8_t get_hex_number(FILE *input){
	uint8_t num = 0;
	int8_t ch = fgetc(input);

	ch = fgetc(input);

	while (!feof(input)){
		switch (ch){
			case '.':
			case ',':
			case ';':
			case '(':
			case ')':
			case '\n':
				fseek(input, -1, SEEK_CUR);
				return num;
			
			default:
				if (isspace(ch))
					return num;
				num *= 16;
				num += get_num(ch);
				break;
			
		}

		ch = fgetc(input);
		
	}

	return num;

}

uint8_t get_num(int8_t ch){
	if (isdigit(ch))
		return ch-'0';
	if (islower(ch))
		return ch-'a'+10;
	if (isupper(ch))
		return ch-'A'+10;
	return 0;
}
