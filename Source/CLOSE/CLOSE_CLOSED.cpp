#include "lib.h"

char fname[] = __FILE__;
char PATH_IN[__CHAR_BUFFER] = "../../Resource/";
char PATH_OUT[__CHAR_BUFFER] = "../../Release/";

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
  path2(PATH_OUT);
  adjust_csv(fout, tt);
  //delete[] tt;
  return 0;
}

void adjust_data(int** A)
{
  // for (i = 0; i < N; i++)
  //{
  //  if (A[i][4] == 22) {
  //   A[i][4] = 21;
  // }
  //}
  for (i = 0; i < N; i++)
  {
    A[i][M] = 0;
  }
}
void adjust_csv(FILE* fout, int** tt)
{
  char csv[N][4][__CHAR_BUFFER];
  char sts[9][__CHAR_BUFFER];
  strcpy(sts[0], "闭锁状态_");
  strcpy(sts[1], "大于或等于设定高度_");
  strcpy(sts[2], "正在关门_");
  strcpy(sts[3], "正在开门_");
  strcpy(sts[4], "停止状态_");
  strcpy(sts[5], "闭锁不完整_");
  strcpy(sts[6], "正在上锁_");
  strcpy(sts[7], "正在解锁_");
  strcpy(sts[8], "解锁强开区_");

  char bcm[8][__CHAR_BUFFER];
  strcpy(bcm[0], "DEFAULT/OFF/ACC/START/INVAILD状态_");
  strcpy(bcm[1], "DEFAULT/OFF/ACC/START/INVAILD状态_");
  strcpy(bcm[2], "DEFAULT/OFF/ACC/START/INVAILD状态_");
  strcpy(bcm[3], "ON状态_");
  strcpy(bcm[4], "DEFAULT/OFF/ACC/START/INVAILD状态_");
  strcpy(bcm[5], "invalid_valid状态_");
  strcpy(bcm[6], "invalid_valid状态_");
  strcpy(bcm[7], "invalid状态_");

  char speed_valid[2][40];
  strcpy(speed_valid[0], "速度无效且");
  strcpy(speed_valid[1], "速度有效且");

  char speed[101][40];
  strcpy(speed[0], "\t0km/h");
  strcpy(speed[2], "\t小于5km/h");
  strcpy(speed[5], "\t5km/h");
  strcpy(speed[100], "大于5km/h");

  char ctrl[45][40];
  strcpy(ctrl[1], "蓝牙开启");
  strcpy(ctrl[2], "蓝牙关闭");
  strcpy(ctrl[12], "远程关闭");
  strcpy(ctrl[13], "远程小角度");
  strcpy(ctrl[21], "大屏关闭");
  strcpy(ctrl[22], "大屏开启");
  strcpy(ctrl[23], "大屏停止");
  strcpy(ctrl[31], "背门外部开关");
  strcpy(ctrl[33], "两次钥匙短按");
  strcpy(ctrl[34], "脚踢信号");
  strcpy(ctrl[36], "一次钥匙短按");
  strcpy(ctrl[40], "背门短按");
  strcpy(ctrl[41], "背门长按");
  strcpy(ctrl[42], "背门超长按");

  char target[10][100];
  strcpy(target[1], "蓝牙开启");
  strcpy(target[2], "蓝牙关闭");

  for (i = 0; i < N; i++)
  {
    int a = tt[i][0]; // sts
    int b = tt[i][1]; // bcm
    int c = tt[i][2]; // speedvalid
    int d = tt[i][3]; // speed
    int e = tt[i][4]; // ctrl
    int f = tt[i][5]; // target

    // Excel第一格
    strcpy(csv[i][0], sts[a]);
    strcat_s(csv[i][0], bcm[b]);
    strcat_s(csv[i][0], ctrl[e]);
    // Excel第二格
    strcat_s(csv[i][1], speed_valid[c]);
    strcat_s(csv[i][1], speed[d]);
    strcat_s(csv[i][1],
             "\n处于正常工作电压范围\n无错误工况（如热保护、通讯故障等）");
    // Excel第三格
    strcpy(csv[i][2], "发送");
    strcat_s(csv[i][2], ctrl[e]);
    strcat_s(csv[i][2], "信号");
    // Excel第四格  结论
    // strcat_s(csv[i][1], "\"");
    // strcat_s(csv[i][1], speed_valid[c]);
    // strcat_s(csv[i][1], speed[d]);

    fprintf_s(fout, "%s,\"%s\",%s,", csv[i][0], csv[i][1], csv[i][2]);

    fprintf_s(fout, "背门处于闭锁状态，不响应关闭/停止指令\n");
    // printf_s("\n%s,%s,%s\n", csv[i][0], csv[i][1], csv[i][2]);
  }
}