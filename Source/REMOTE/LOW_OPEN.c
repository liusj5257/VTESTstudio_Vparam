/**
 *@file LOW_OPEN.c
 *@author LIU (liu_shaojun@outlook.com)
 *@brief
 *?@version 0.1
 *@date 2022-12-27
 *
 *@copyright Copyright (c) 2022
 *
 **/

#include "lib.h"
/**
 *@brief
 *?读取文件地址名称并存为全局字符串
 **/
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
    if (data[i][gColumn] == 0) {
      strcpy(csv[i][3], gState.mResult[0]);
    } else {
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
    if (data[i][0] == 1 || data[i][0] == 4) {
      data[i][gColumn] = data[i][0];
    } else if ((data[i][0] == 0 || data[i][0] == 8) && //! open stop
               (data[i][1] == 0 || data[i][1] == 1 || data[i][1] == 7 ||
                data[i][1] == 2 || //! speed power_mode
                data[i][1] == 4 ||
                (data[i][1] == 3 && data[i][3] < 5 && data[i][2] == 1)) &&
               data[i][4] == 2) //! success
    {
      data[i][gColumn] = 4;
    } else {
      data[i][gColumn] = data[i][0];
    }
  }
}

// void adjust_csv(FILE* fout, int** tt)
// {
//   char csv[N][4][__CHAR_BUFFER];
//   char sts[9][__CHAR_BUFFER];
//   strcpy(sts[0], "闭锁状态_");
//   strcpy(sts[1], "大于或等于设定高度_");
//   strcpy(sts[2], "正在关门_");
//   strcpy(sts[3], "正在开门_");
//   strcpy(sts[4], "停止状态_");
//   strcpy(sts[5], "闭锁不完整_");
//   strcpy(sts[6], "正在上锁_");
//   strcpy(sts[7], "正在解锁_");
//   strcpy(sts[8], "解锁强开区_");

//   char bcm[8][__CHAR_BUFFER];
//   strcpy(bcm[0], "DEFAULT状态_");
//   strcpy(bcm[1], "OFF状态_");
//   strcpy(bcm[2], "ACC状态_");
//   strcpy(bcm[3], "ON状态_");
//   strcpy(bcm[4], "START状态_");
//   strcpy(bcm[5], "invalid_valid状态_");
//   strcpy(bcm[6], "invalid_valid状态_");
//   strcpy(bcm[7], "invalid状态_");

//   char speed_valid[2][40];
//   strcpy(speed_valid[0], "速度无效且");
//   strcpy(speed_valid[1], "速度有效且");

//   char speed[101][40];
//   strcpy(speed[0], "\t0km/h");
//   strcpy(speed[2], "\t小于5km/h");
//   strcpy(speed[5], "\t5km/h");
//   strcpy(speed[100], "大于5km/h");

//   char ctrl[45][40];
//   strcpy(ctrl[1], "蓝牙开启");
//   strcpy(ctrl[2], "蓝牙关闭");
//   strcpy(ctrl[12], "远程关闭");
//   strcpy(ctrl[13], "远程小角度");
//   strcpy(ctrl[21], "大屏关闭");
//   strcpy(ctrl[22], "大屏开启");
//   strcpy(ctrl[23], "大屏停止");
//   strcpy(ctrl[31], "背门外部开关");
//   strcpy(ctrl[33], "两次钥匙短按");
//   strcpy(ctrl[34], "脚踢信号");
//   strcpy(ctrl[36], "一次钥匙短按");
//   strcpy(ctrl[40], "背门短按");
//   strcpy(ctrl[41], "背门长按");
//   strcpy(ctrl[42], "背门超长按");

//   char target[10][100];
//   strcpy(target[1], "蓝牙开启");
//   strcpy(target[2], "蓝牙关闭");

//   char sig[10][100];
//   strcpy(sig[0], "认证中");
//   strcpy(sig[1], "认证失败");
//   strcpy(sig[2], "认证成功");
//   strcpy(sig[3], "未认证");

//   for (i = 0; i < N; i++)
//   {
//     int a = tt[i][0]; // sts
//     int b = tt[i][1]; // bcm
//     int c = tt[i][2]; // speedvalid
//     int d = tt[i][3]; // speed
//     int e = tt[i][4]; // sig
//     int f = tt[i][5]; // ctrl
//     int g = tt[i][6]; // target

//     // Excel第一格
//     strcpy(csv[i][0], sts[a]);
//     strcat_s(csv[i][0], bcm[b]);
//     strcat_s(csv[i][0], ctrl[f]);
//     // Excel第二格
//     strcat_s(csv[i][1], speed_valid[c]);
//     strcat_s(csv[i][1], speed[d]);
//     strcat_s(csv[i][1], "\n");
//     strcat_s(csv[i][1], sig[e]);
//     strcat_s(csv[i][1],
//              "\n处于正常工作电压范围\n无错误工况（如热保护、通讯故障等）");
//     // Excel第三格
//     strcpy(csv[i][2], "发送");
//     strcat_s(csv[i][2], ctrl[f]);
//     strcat_s(csv[i][2], "信号");
//     // Excel第四格  结论
//     // strcat_s(csv[i][1], "\"");
//     // strcat_s(csv[i][1], speed_valid[c]);
//     // strcat_s(csv[i][1], speed[d]);

//     fprintf_s(fout, "%s,\"%s\",%s,", csv[i][0], csv[i][1], csv[i][2]);

//     if ((tt[i][0] == 0 || tt[i][0] == 8) && //! open stop
//         (tt[i][1] == 0 || tt[i][1] == 1 || tt[i][1] == 7 ||
//          tt[i][1] == 2 || //! speed power_mode
//          tt[i][1] == 4 || (tt[i][1] == 3 && tt[i][3] < 5 && tt[i][2] == 1))
//          &&
//         tt[i][4] == 2) //! success
//     {
//       fprintf_s(fout, "蜂鸣器间鸣，背门响应开启至小角度打开状态\n");
//     }

//     // else if (tt[i][4] != 2)
//     // {
//     //   fprintf_s(fout, "背门不响应指令\n");
//     // }
//     // else if (tt[i][1] == 3 && tt[i][2] == 0)
//     // {
//     //   fprintf_s(fout, "背门不响应指令\n");
//     // }
//     // else if (tt[i][1] == 3 && tt[i][3] >= 5)
//     // {
//     //   fprintf_s(fout, "背门不响应指令\n");
//     // }
//     // else if (tt[i][1] == 5 || tt[i][1] == 6)
//     // {
//     //   fprintf_s(fout, "背门不响应指令\n");
//     // }
//     else
//       fprintf_s(fout, "背门不响应指令\n");
//   }
// }