#ifndef _MY_LIB__
#define _MY_LIB__

// #include <cstdio>
// #include <cstdlib>
// #include <cstring>
// #include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// using namespace std;
#define __CHAR_BUFFER 1000
extern void adjust_data(int** data);
extern void output_data(FILE* fout, int** data);
extern int** init_data(int gRow, int gColumn);
extern void input_data(FILE* fin, int** data);
extern void init_str_column(char* str, int size, FILE* file);
extern void fpath(FILE** fin, FILE** fout, FILE** fin2);
extern void path(char fname[__CHAR_BUFFER], char path_in[__CHAR_BUFFER],
                 char path_out[__CHAR_BUFFER]);
extern void init_row(FILE* file);
extern void char_out(int** data);

extern void adjust_csv(char path_out[__CHAR_BUFFER], int** data);

extern int gRow, gColumn;
extern char gTempC[__CHAR_BUFFER];
extern FILE* gFin;
extern FILE* gFout;

extern const int kSix;
extern const int kNine;

extern char gPathIn[__CHAR_BUFFER];
extern char gPathOut[__CHAR_BUFFER];

#endif