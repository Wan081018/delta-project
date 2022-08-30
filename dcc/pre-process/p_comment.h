//
//
//

#ifndef __P_COMMENT_H__

#define __P_COMMENT_H__

#include <stdio.h>

// ignore comment
extern int comment(FILE *fin, FILE *fout);

// line comment
extern int line_comment(FILE *fin, FILE *fout);

// division comment
extern int div_comment(FILE *fin, FILE *fout);


#endif

