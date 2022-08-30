//
//
//

#ifndef __P_CHAR_H__

#define __P_CHAR_H__

#include <stdio.h>

// escape character set
extern int esc[300];

// init escape character set
extern int init_esc();

// turn chacacter into hexadecimal form
extern int character(FILE *fin, FILE *fout);

// normal character
extern int hex_char(int ch);

// escape charcter
extern int escape(int ch);


#endif

