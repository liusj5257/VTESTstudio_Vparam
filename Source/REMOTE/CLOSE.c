#include "lib.h"

char gFname[] = __FILE__;

int main() {
  gFunction = REMOTE_CLOSE;
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
    int mapSts = data[i][0];
    int mapBcm = data[i][1];
    int mapSpeedValid = data[i][2];
    int mapSpeed = data[i][3];
    int mapSig = data[i][4];
    int mapCtrl = data[i][5];
    int mapTarget = data[i][6];
    //! Excel第一格
    strcpy(csv[i][0], gState.mSts[mapSts]);
    strcat(csv[i][0], gState.mBcm[mapBcm]);
    strcat(csv[i][0], gState.mCtrl[mapCtrl]);
    //! Excel第二格
    strcpy(csv[i][1], gState.mSpeedValid[mapSpeedValid]);
    strcat(csv[i][1], gState.mSpeed[mapSpeed]);
    strcat(csv[i][1], "\n");
    strcat(csv[i][1], gState.mSig[mapSig]);
    strcat(csv[i][1],
           "\n处于正常工作电压范围\n无错误工况（如热保护、通讯故障等）");
    //! Excel第三格
    strcpy(csv[i][2], "发送");
    strcat(csv[i][2], gState.mCtrl[mapCtrl]);
    strcat(csv[i][2], "信号");
    //! Excel第四格
    if ((data[i][0] == 1 || data[i][0] == 4) && //! open stop
        (data[i][1] == 0 || data[i][1] == 1 || data[i][1] == 7 ||
         data[i][1] == 2 || data[i][1] == 4 ||
         (data[i][1] == 3 && data[i][3] < 5 && data[i][2] == 1)) &&
        data[i][4] == 2) {
      strcpy(csv[i][3], gState.mResult[0]);
    } else if ((data[i][0] == 8) && //! EOA
               (data[i][1] == 0 || data[i][1] == 1 || data[i][1] == 7 ||
                data[i][1] == 2 || data[i][1] == 4 ||
                (data[i][1] == 3 && data[i][3] < 5 && data[i][2] == 1)) &&
               data[i][4] == 2) {
      strcpy(csv[i][3], gState.mResult[2]);
    }

    else {
      strcpy(csv[i][3], gState.mResult[1]);
    }
    //? csv 每个格子以“,”分割，一个格子包含多行用“"str"”。
    fprintf(gFout, "%s,\"%s\",%s,%s\n", csv[i][0], csv[i][1], csv[i][2],
            csv[i][3]);
  }
}
void adjust_data(int **data) {
  int i = 0;
  for (i = 0; i < gRow; i++) {
    if ((data[i][0] == 1 || data[i][0] == 4) && //! open stop
        (data[i][1] == 0 || data[i][1] == 1 || data[i][1] == 7 ||
         data[i][1] == 2 || data[i][1] == 4 ||
         (data[i][1] == 3 && data[i][3] < 5 && data[i][2] == 1)) &&
        data[i][4] == 2) //! success
    {
      data[i][gColumn] = 0;
    } else if ((data[i][0] == 8) && //! EOA
               (data[i][1] == 0 || data[i][1] == 1 || data[i][1] == 7 ||
                data[i][1] == 2 || data[i][1] == 4 ||
                (data[i][1] == 3 && data[i][3] < 5 && data[i][2] == 1)) &&
               data[i][4] == 2) //! success
    {
      data[i][gColumn] = 4;
    }

    else {
      data[i][gColumn] = data[i][0];
    }
  }
}
