
#include "lib.h"
char fname[] = __FILE__;
char PATH_IN[__CHAR_BUFFER] = "../../INPUT/STOP/";
char PATH_OUT[__CHAR_BUFFER] = "../../OUTPUT/STOP/";
int main(int argc, char* argv[])
{
  // fpath(a, b, a2);
  path(fname, PATH_IN, PATH_OUT);    //?路径
  init_N(fin2);                      //?初始化N
  init_str_M(c, __CHAR_BUFFER, fin); //?读取前置定义以及初始化M
  int** tt = init_data(N, M + 1);    //*建立数据库
  input_data(fin, tt);               //?读取数据
  adjust_data(tt);                   //?调整数据
  output_data(fout, tt);             //!输出文件
  return 0;
}

void adjust_data(int** A)
{
  for (i = 0; i < N; i++)
  {
    if (A[i][4] == 33)
    {
      A[i][4] = 36;
    }
  }
  for (i = 0; i < N; i++)
  {
    // if (A[i][1] == 0 || A[i][1] == 1 || A[i][1] == 7 || A[i][1] == 2 ||
    //     A[i][1] == 4 || (A[i][1] == 3 && A[i][3] < 5 && A[i][2] == 1)) {
    //   A[i][M] = 4;
    // } else if (A[i][0] == 2) {
    //   A[i][M] = 0;
    // } else
    A[i][M] = 4;
  }
}
