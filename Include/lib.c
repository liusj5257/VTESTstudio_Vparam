#include "lib.h"
#include <stdio.h>
#include <string.h>

int gRow = 0;
int gColumn = 0;
const int kSix = 6;
const int kNine = 9;

char gTempC[__CHAR_BUFFER];
/**
 *@brief 定义全局字符串,输入输出文件路径
 **/
char gPathIn[__CHAR_BUFFER] = "../../Resource/";
char gPathOut[__CHAR_BUFFER] = "../../Release/";

enum FUNCTIONS gFunction;
state gState;

FILE *gFin = 0;
FILE *gFout = 0;

void output_data(FILE *fout, int **data) {
  int i = 0;
  int j = 0;
  fprintf(fout, "%s", gTempC);
  for (i = 0; i < gRow; i++) {
    fprintf(fout, "\t\t");
    for (j = 0; j < gColumn + 1; j++) {
      fprintf(fout, "%d\t", data[i][j]);
    }
    fprintf(fout, "\n");
  }
  int aaa = fclose(fout);
  printf("success!");
}

int **init_data(int gRow, int gColumn) {
  int i = 0;
  int j = 0;
  // int** data = new int*[gRow];
  //! 内存分配一个包含 gRow 个int型指针的数组
  int **data = (int **)malloc(sizeof(int *) * gRow);
  for (int i = 0; i < gRow; ++i) {
    data[i] = (int *)malloc(sizeof(int) * gColumn);
  }
  for (i = 0; i < gRow; i++) {
    for (j = 0; j < gColumn; j++) {
      data[i][j] = 0;
      // printf("%d\t", data[i][j]);
    }
  }
  return data;
}

void init_row(FILE *file) {
  char gTempC = 0;
  while (gTempC = (char)fgetc(file), gTempC != EOF) {
    if (gTempC == '\n') {
      gRow++; /* code */
    }
  }
  // ！实际行数
  gRow -= kNine;
  printf("gRow = %d\t", gRow);
  rewind(file);
  // fclose(file);
  //  gColumn = 5;
}
void init_str_column(char *str, int size, FILE *file) {
  int i = 0;
  int j = 0;
  char gTempC = 0;
  while (gTempC = (char)fgetc(file),
         j <= kSix + 1 && gTempC != EOF && i < size - 1) {
    if (j == kSix && gTempC == 'I') {
      gColumn++;
    }
    if (j == kSix && gTempC == 'S') {
      str[i++] = 'A';
      str[i++] = 'u';
      str[i++] = 't';
      str[i++] = 'o';
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
    } else {
      if (gTempC == '\n') {
        if (j == 4) {
          str[i++] = '_';
          str[i++] = 'O';
          str[i++] = 'U';
          str[i++] = 'T';
        }
        j++;
      }
      str[i] = gTempC;
      ++i;
    }
  }
  printf("gColumn = %d\t", gColumn);
  str[i] = gTempC;
  ++i;
  j = 0;
  while (gTempC = (char)fgetc(file), j <= 4) {
    j++;
    str[i] = gTempC;
    ++i;
  }
  if (gTempC != '\n') {
    ungetc(gTempC, stdin);
  }
  str[i] = '\0';
}
void input_data(FILE *fin, int **data) {
  int i = 0;
  int j = 0;
  for (i = 0; i < gRow; i++) {
    for (j = 0; j < gColumn; j++) {
      fscanf_s(fin, "%d", &data[i][j]);
    }
  }
  fclose(fin);
}

void path(char fname[__CHAR_BUFFER], char path_in[__CHAR_BUFFER],
          char path_out[__CHAR_BUFFER]) {
  // ？截取路径
  char *cutFname = strstr(fname, "e\\") + 2;
  char *tempC = strrchr(cutFname, '\\');
  *tempC = '/';
  // ？组合路径
  strcat(path_in, cutFname);
  strcat(path_out, cutFname);
  //?删除.c后缀
  path_in[strlen(path_in) - 2] = '\0';
  path_out[strlen(path_out) - 2] = '\0';
  //?添加后缀
  strcat(path_in, (char *)".vparam");
  strcat(path_out, (char *)"_OUT.vparam");
  gFin = fopen(path_in, "r+");
  gFout = fopen(path_out, "w+");
  printf("Data读取路径\n%s\n", path_in);
}

void init_struct() {
  strcpy(gState.mPassSeatSts[0], "副驾undefd1");
  strcpy(gState.mPassSeatSts[1], "副驾未占位");
  strcpy(gState.mPassSeatSts[2], "副驾占位");
  strcpy(gState.mPassSeatSts[3], "副驾undefd2");
  strcpy(gState.mDoorPassSts[0], "副驾门Ukwn状态");
  strcpy(gState.mDoorPassSts[1], "副驾门开启状态");
  strcpy(gState.mDoorPassSts[2], "副驾门关闭状态");
  strcpy(gState.mDoorDrvrSts[0], "主驾门Ukwn状态");
  strcpy(gState.mDoorDrvrSts[1], "主驾门开启状态");
  strcpy(gState.mDoorDrvrSts[2], "主驾门关闭状态");
  switch (gFunction) {
  case WelcomeDrv:
    strcpy(gState.mResult[0], "旋转屏无响应");
    strcpy(gState.mResult[1], "旋转屏旋转至主驾极限位置");
    strcpy(gState.mResult[2], "旋转屏旋转至副驾极限位置");
    break;
  default: {
    printf("fail\n");
  } break;
  }
}