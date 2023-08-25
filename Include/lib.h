#ifndef _MY_LIB__
#define _MY_LIB__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __CHAR_BUFFER 1000
// #define remote_close 1

extern void init_struct();
extern void adjust_data(int **data);
extern void output_data(FILE *fout, int **data);
extern void input_data(FILE *fin, int **data);
extern void init_str_column(char *str, int size, FILE *file);
extern void fpath(FILE **fin, FILE **fout, FILE **fin2);
extern void path(char fname[__CHAR_BUFFER], char path_in[__CHAR_BUFFER],
                 char path_out[__CHAR_BUFFER]);
extern void init_row(FILE *file);
extern void char_out(int **data);
extern void adjust_csv(char path_out[__CHAR_BUFFER], int **data);

extern const int kSix;
extern const int kNine;
extern int gRow;
extern int gColumn;

extern int **init_data(int gRow, int gColumn);

extern char gTempC[__CHAR_BUFFER];
extern char gPathIn[__CHAR_BUFFER];
extern char gPathOut[__CHAR_BUFFER];

extern FILE *gFin;
extern FILE *gFout;
/**
**@brief 定义测试类型,区分CSV测试结论
**
**/
enum FUNCTIONS { WelcomeDrv, GuestSending };
extern enum FUNCTIONS gFunction;
/**
**@brief 定义CSV通用字符串
**
**/
typedef struct states {
  char mPassSeatSts[10][__CHAR_BUFFER];
  char mDoorPassSts[10][__CHAR_BUFFER];
  char mDoorDrvrSts[10][__CHAR_BUFFER];
  char mSunflowerScreenSldgSwt[35][__CHAR_BUFFER];
  char mSunflowerAnticlmp[10][__CHAR_BUFFER];
  char mSunflowerScreenSmtSteerMstSwt[2][__CHAR_BUFFER];
  char mSunflowerScreenCinemaModSetting[10][__CHAR_BUFFER];
  char mSunflowerScreenPrkgSetting[10][__CHAR_BUFFER];
  char mGearLvrIndcn[10][__CHAR_BUFFER];
  char mDrvrSeatSts[10][__CHAR_BUFFER];
  char mActvnOfWelcomeLi[10][__CHAR_BUFFER];
  char mSunflowerScreenWelcomeGuestSwt[10][__CHAR_BUFFER];
  char mResult[10][__CHAR_BUFFER];
} state;
extern state gState;

#endif