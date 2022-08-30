#include "lib.h"
//#include <stdlib.h>

int gRow = 0;
int gColumn = 0;

const int kSix = 6;
const int kNine = 9;

char gTempC[__CHAR_BUFFER];
char gPathIn[__CHAR_BUFFER] = "../../Resource/";
char gPathOut[__CHAR_BUFFER] = "../../Release/";

FILE* gFin = 0;
FILE* gFout = 0;
// FILE* fin2 = 0;
//  FILE* fout2 = 0;

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
  printf("Data读取路径\n%s\n", path_in);
  //！打开文件
  gFin = fopen(path_in, "r+");
  // fin2 = fopen(path_in, "r+");
  gFout = fopen(path_out, "w+");
}

void path2(char path_out[__CHAR_BUFFER])
{
  gFin = fopen(path_out, "r");
  printf_s("\nVparam\n%s", path_out);
  char* a = strrchr(path_out, '.');
  strcpy(a, ".csv");
  printf_s("\nReport\n%s", path_out);
  gFout = fopen(path_out, "w+");
}
