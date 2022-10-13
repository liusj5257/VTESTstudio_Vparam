#include "lib.h"
#include <stdio.h>
#include <string.h>

int gRow = 0;
int gColumn = 0;

const int kSix = 6;
const int kNine = 9;

char gTempC[__CHAR_BUFFER];
char gPathIn[__CHAR_BUFFER] = "../../Resource/";
char gPathOut[__CHAR_BUFFER] = "../../Release/";

enum FUNCTIONS gFunction;
state gState;

FILE* gFin = 0;
FILE* gFout = 0;

void output_data(FILE* fout, int** data)
{
  int i = 0;
  int j = 0;
  fprintf(fout, "%s", gTempC);
  for (i = 0; i < gRow; i++)
  {
    fprintf(fout, "\t\t");
    for (j = 0; j < gColumn + 1; j++)
    {
      fprintf(fout, "%d\t", data[i][j]);
    }
    fprintf(fout, "\n");
  }
  int aaa = fclose(fout);
  printf("success!");
}

int** init_data(int gRow, int gColumn)
{
  int i = 0;
  int j = 0;
  // int** data = new int*[gRow];
  //!内存分配一个包含 gRow 个int型指针的数组
  int** data = (int**)malloc(sizeof(int*) * gRow);
  for (int i = 0; i < gRow; ++i)
  {
    data[i] = (int*)malloc(sizeof(int) * gColumn);
  }
  for (i = 0; i < gRow; i++)
  {
    for (j = 0; j < gColumn; j++)
    {
      data[i][j] = 0;
      // printf("%d\t", data[i][j]);
    }
  }
  return data;
}

void init_row(FILE* file)
{
  char gTempC = 0;
  while (gTempC = (char)fgetc(file), gTempC != EOF)
  {
    if (gTempC == '\n')
    {
      gRow++; /* code */
    }
  }
  //！实际列数
  gRow -= kNine;
  printf("gRow = %d\t", gRow);
  rewind(file);
  // fclose(file);
  //  gColumn = 5;
}
void init_str_column(char* str, int size, FILE* file)
{
  int i = 0;
  int j = 0;
  char gTempC = 0;
  while (gTempC = (char)fgetc(file),
         j <= kSix + 1 && gTempC != EOF && i < size - 1)
  {
    if (j == kSix && gTempC == 'I')
    {
      gColumn++;
    }
    if (j == kSix && gTempC == 'S')
    {
      str[i++] = 'A';
      str[i++] = 'u';
      str[i++] = 't';
      str[i++] = 'o';
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
      gTempC = (char)fgetc(file);
    }
    else
    {
      if (gTempC == '\n')
      {
        if (j == 4)
        {
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
  while (gTempC = (char)fgetc(file), j <= 4)
  {
    j++;
    str[i] = gTempC;
    ++i;
  }
  if (gTempC != '\n')
  {
    ungetc(gTempC, stdin);
  }
  str[i] = '\0';
}
void input_data(FILE* fin, int** data)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < gRow; i++)
  {
    for (j = 0; j < gColumn; j++)
    {
      fscanf_s(fin, "%d", &data[i][j]);
    }
  }
  fclose(fin);
}

void path(char fname[__CHAR_BUFFER], char path_in[__CHAR_BUFFER],
          char path_out[__CHAR_BUFFER])
{
  //？截取路径
  char* cutFname = strstr(fname, "e\\") + 2;
  char* tempC = strrchr(cutFname, '\\');
  *tempC = '/';
  //？组合路径
  strcat(path_in, cutFname);
  strcat(path_out, cutFname);
  //?删除.c后缀
  path_in[strlen(path_in) - 2] = '\0';
  path_out[strlen(path_out) - 2] = '\0';
  //?添加后缀
  strcat(path_in, (char*)".vparam");
  strcat(path_out, (char*)"_OUT.vparam");
  gFin = fopen(path_in, "r+");
  gFout = fopen(path_out, "w+");
  printf("Data读取路径\n%s\n", path_in);
}

void init_struct()
{
  strcpy(gState.mSts[0], "闭锁状态_");
  strcpy(gState.mSts[1], "大于或等于设定高度_");
  strcpy(gState.mSts[2], "正在关门_");
  strcpy(gState.mSts[3], "正在开门_");
  strcpy(gState.mSts[4], "停止状态_");
  strcpy(gState.mSts[5], "闭锁不完整_");
  strcpy(gState.mSts[6], "正在上锁_");
  strcpy(gState.mSts[7], "正在解锁_");
  strcpy(gState.mSts[8], "解锁强开区_");
  strcpy(gState.mBcm[0], "DEFAULT状态_");
  strcpy(gState.mBcm[1], "OFF状态_");
  strcpy(gState.mBcm[2], "ACC状态_");
  strcpy(gState.mBcm[3], "ON状态_");
  strcpy(gState.mBcm[4], "START状态_");
  strcpy(gState.mBcm[5], "invalid_valid状态_");
  strcpy(gState.mBcm[6], "invalid_valid状态_");
  strcpy(gState.mBcm[7], "invalid状态_");
  strcpy(gState.mSpeedValid[0], "速度无效且");
  strcpy(gState.mSpeedValid[1], "速度有效且");
  strcpy(gState.mSpeed[0], "0km/h");
  strcpy(gState.mSpeed[2], "小于5km/h");
  strcpy(gState.mSpeed[5], "5km/h");
  strcpy(gState.mSpeed[100], "大于5km/h");
  strcpy(gState.mCtrl[1], "蓝牙开启");
  strcpy(gState.mCtrl[2], "蓝牙关闭");
  strcpy(gState.mCtrl[12], "远程关闭");
  strcpy(gState.mCtrl[13], "远程小角度");
  strcpy(gState.mCtrl[21], "大屏关闭");
  strcpy(gState.mCtrl[22], "大屏开启");
  strcpy(gState.mCtrl[23], "大屏停止");
  strcpy(gState.mCtrl[31], "背门外部开关");
  strcpy(gState.mCtrl[33], "两次钥匙短按");
  strcpy(gState.mCtrl[34], "脚踢信号");
  strcpy(gState.mCtrl[36], "一次钥匙短按");
  strcpy(gState.mCtrl[40], "背门短按");
  strcpy(gState.mCtrl[41], "背门长按");
  strcpy(gState.mCtrl[42], "背门超长按");
  strcpy(gState.mTarget[1], "???");
  strcpy(gState.mTarget[2], "???");
  strcpy(gState.mSig[0], "认证中");
  strcpy(gState.mSig[1], "认证失败");
  strcpy(gState.mSig[2], "认证成功");
  strcpy(gState.mSig[3], "未认证");
  switch (gFunction)
  {
    case REMOTE_CLOSE:
      strcpy(gState.mResult[0], "蜂鸣器间鸣，背门响应关闭至闭锁状态");
      strcpy(gState.mResult[1], "背门不响应远程指令");
      break;
    default: {
      printf("fail\n");
    }
    break;
  }
}