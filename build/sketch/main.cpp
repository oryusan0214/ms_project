#line 1 "C:\\WORK\\学校\\未来創造展\\ms_project\\ms_project\\main.cpp"
/* -------------------------------------------------------------------------- */
/* start.ino																 																  */
/* 初期化機能												 												                  */
/* アプリケーションエントリーポイントです。(Arduinoではここが								  */
/*																					エントリポジションです。)					*/
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴								日付　氏名																  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成								2023/12/04　山田龍之介		 								  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  														*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "main.h"


int main(){
  UCHR legbusy[18]={0};
  UCHR armbusy[2]={0};
  uint16_t gyro_data[6]={0,0,0,0,0,0};

  /*受信データを取得*/
  
  /*busy信号検出*/
  msServoGetBusy(legbusy,sizeof(legbusy)/sizeof(legbusy[0]));
  msDCGetBusy(armbusy,sizeof(armbusy)/sizeof(armbusy[0]));

  /*ジャイロデータ取得*/
  gyro_get(gyro_get);

  /*送信データを作成*/


  return 0;
}

