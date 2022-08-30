//
//
//

#include "global.h"
#include "p_char.h"
#include "put_error.h"

int esc[300];

// octal escape character is not valid

int init_esc(){
	esc['0'] = '\0';
	esc['a'] = '\a';
	esc['n'] = '\n';
	esc['b'] = '\b';
	esc['f'] = '\f';
	esc['r'] = '\r';
	esc['t'] = '\t';
	esc['v'] = '\v';
	esc['\\'] = '\\';
	esc['\''] = '\'';
	esc['\"'] = '\"';
	esc['?'] = '?';
	return 0;
}

int character(FILE *fin, FILE *fout){
	int ch, cnt = 0;
	while (~(ch = fgetc(fin))){
		if (ch == '\''){
			if (cnt != 1){
				put_error(); // not a character
				return 1;
			}
			return 0;
		}
		++cnt;
		if (ch == '\\'){
			ch = fgetc(fin);
			int h_ch = escape(ch);
			if (~h_ch)
				fprintf(fout, "%x", h_ch);
		} else{
			int h_ch = hex_char(ch);
			if (~h_ch)
				fprintf(fout, "%x", h_ch);
		}
	}
	
	put_error(); // unterminated character
	return 1;
}

int hex_char(int ch){
	if (ch == ' ')
		return ' ';
	if (isspace(ch))
		return -1;
	return ch;
}

int escape(int ch){
	if (ch == ' ')
		return ' ';
	if (isspace(ch))
		return -1;
	if (ch == 'x'){
		;
	}
	return esc[ch];
}

