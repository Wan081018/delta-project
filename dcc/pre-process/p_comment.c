//
//
//

#include "global.h"
#include "p_comment.h"
#include "put_error.h"

int comment(FILE *fin, FILE *fout){
	int ch = fgetc(fin);
	if (ch == '/'){                    // line comment
		line_comment(fin, fout);
	} else if (ch == '*'){             // division comment
		if (div_comment(fin, fout))
			return 1;
	} else{                            // not a comment
		fputc('/', fout);
		fputc(ch, fout);
	}
	return 0;
}

int line_comment(FILE *fin, FILE *fout){
	int ch = fgetc(fin);
	while (ch!='\n' && ~ch)
		ch = fgetc(fin);
	fputc('\n', fout);
	return 0;
}

int div_comment(FILE *fin, FILE *fout){
	int ch;
	while (~(ch = fgetc(fin))){
		if (ch == '*'){
			ch = fgetc(fin);
			if (!ch)
				break;
			if (ch == '/')
				return 0;
		}
		if (ch == '\n')
			fputc(ch, fout);
	}

	put_error(); // unterminated comment
	return 1;
}

