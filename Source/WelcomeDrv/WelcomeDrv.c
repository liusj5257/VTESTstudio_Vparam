#include "lib.h"

#define PassSeatSts2 data[i][0]
#define DoorPassSts data[i][1]
#define DoorDrvrSts data[i][2]
#define Res data[i][3]

char gFname[] = __FILE__;

int main() {
  gFunction = WelcomeDrv;
  path(gFname, gPathIn, gPathOut);
  init_row(gFin);
  init_str_column(gTempC, __CHAR_BUFFER, gFin);
  int **data = init_data(gRow, gColumn + 1);
  input_data(gFin, data);
  adjust_data(data);
  output_data(gFout, data);
  init_struct();
  adjust_csv(gPathOut, data);
  free(data);
  return 0;
}

void adjust_csv(char path_out[__CHAR_BUFFER], int **data) {
  gFin = fopen(path_out, "r");
  printf_s("\nVparam\n%s", path_out);
  char *a = strrchr(path_out, '.');
  strcpy(a, ".csv");
  printf_s("\nReport\n%s", path_out);
  gFout = fopen(path_out, "w+");
  //! 用例个数，4个输出格子，字符串长度
  char csv[gRow][4][__CHAR_BUFFER];
  int i = 0;
  for (i = 0; i < gRow; i++) {
    int mPassSeatSts = PassSeatSts2;
    int mDoorPassSts = DoorPassSts;
    int mDoorDrvrSts = DoorDrvrSts;
    int mRes = Res;
    //! Excel第一格
    strcpy(csv[i][0], gState.mPassSeatSts[mPassSeatSts]);
    strcat(csv[i][0], "_");
    strcat(csv[i][0], gState.mDoorPassSts[mDoorPassSts]);
    strcat(csv[i][0], "_");
    strcat(csv[i][0], gState.mDoorDrvrSts[mDoorDrvrSts]);
    //! Excel第二格
    strcpy(csv[i][1], "1.初始旋转屏至中间位置\'16\'\n");
    strcat(csv[i][1], "2.开启智能转向开关,迎送宾功能,整车迎宾信号\n");
    strcat(csv[i][1], "3.设置信号:");
    strcat(csv[i][1], gState.mPassSeatSts[mPassSeatSts]);
    strcat(csv[i][1], "_");
    strcat(csv[i][1], gState.mDoorPassSts[mDoorPassSts]);
    strcat(csv[i][1], "_");
    strcat(csv[i][1], gState.mDoorDrvrSts[mDoorDrvrSts]);

    //! Excel第三格
    strcpy(csv[i][2], gState.mResult[mRes]);

    //! Excel第四格
    strcpy(csv[i][3], "迎送宾功能");
    //? csv 每个格子以“,”分割，一个格子包含多行用“"str"”。
    fprintf(gFout, "%s,\"%s\",%s,%s\n", csv[i][0], csv[i][1], csv[i][2],
            csv[i][3]);
  }
}
void adjust_data(int **data) {
  int i = 0;
  for (i = 0; i < gRow; i++) {
    if ((PassSeatSts2 != 2 && DoorDrvrSts == 1) ||
        (DoorDrvrSts == 1) && DoorPassSts != 1)
      Res = 1;
    else if (DoorPassSts == 1 && PassSeatSts2 == 2 && DoorDrvrSts == 2)
      Res = 2;
    ;
  }
}
