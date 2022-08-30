// 
//
//

#include "global.h"
#include "pre_process.h"
#include "put_error.h"

int pre_process(char *source, char *object){
	FILE *fin = fopen(source, "r"),
	     *fout= fopen(object, "w");
	init_esc();

	if (!fin){                         // no such file or directory
		put_error(1);
		fclose(fin);
		fclose(fout);
		return 1;
	}

	int ch, fg = 0;
	while (~(ch = fgetc(fin))){
		if (ch == '\"')                // change string
			fg |= string(fin, fout);
		else if (ch == '\'')           // change character
			fg |= character(fin, fout);
		else if (ch == '/')            // ignore comment
			fg |= comment(fin, fout);
		else if (isdigit(ch))          // change number
			fg |= number(fin, fout, ch);
		else
			fputc(ch, fout);
	}

	if (fg)
		remove(object);

	fclose(fin);
	fclose(fout);
	return fg;
}

