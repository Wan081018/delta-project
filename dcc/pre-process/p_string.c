//
//
//

#include "global.h"
#include "p_string.h"
#include "p_char.h"
#include "put_error.h"

int string(FILE *fin, FILE *fout){
	int ch, fg = 0;
	fputc('[', fout);
	while (~(ch = fgetc(fin))){
		if (ch == '\"'){
			fputc(']', fout);
			return 0;
		}
		if (fg)
			fputc(',', fout);
		if (ch == '\\'){
			ch = fgetc(fin);
			int h_ch = escape(ch);
			if (~h_ch){
				fg = 1;
				fprintf(fout, "%x", h_ch);
			} else
				fg = 0;
		} else{
			int h_ch = hex_char(ch);
			if (~h_ch){
				fg = 1;
				fprintf(fout, "%x", h_ch);
			} else
				fg = 0;
		}
	}

	put_error(); // unterminated string
	return 1;
}

