#line 1 "C:\\WORK\\学校\\未来創造展\\ms_project\\ms_project\\rod.h"
/* -------------------------------------------------------------------------- */
/* rod.h																  */
/* ＣＬ２３・ＳＤ３２・ＲＤ４Ｃ												  */
/* ROD制御に係るヘッダ															  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴								日付		氏名		  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成								2013/05/08	桝井　隆治	  */
/* 000001   機能追加                                2023/12/06  筈尾　辰也       */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include "common.h"							    /* システム共通ヘッダ		  */

/* -------------------------------------------------------------------------- */
/* define宣言																  */
/* -------------------------------------------------------------------------- */
#define ROD_OK            (    0 )			/* 成功						  */
#define ROD_NG            (   -1 )			/* 失敗						  */
#define ROD_PARAM         (   -2 )			/* 引数エラー				  */
#define ROD_READY         (    0 )			/* サーボ待機				  */
#define ROD_BUSY          (    3 )			/* サーボビジー				  */
#define ROD_NOSET       ( 0xEFFF )			/* サーボ設定無し			  */
#define ROD_SPEED           4095            /* RODモータの出力値              */

#define ROD_DST_MIN             0             /* RODモータの最大距離          */
#define ROD_DST_MAX            50             /* RODモータの最小角距離         */

#define ROD                      2            /* RODのID                   */

#define ROD_PIN                  2            /* RODのピン                */
#define ROD_DIR_PIN              8           /* RODの方向判断 */

#define ROD_END1_PIN            18            /* 昇降機のDCのエンコーダ用PIN1   */
#define ROD_END2_PIN            24            /* 昇降機のDCのエンコーダ用PIN2  */

#define ROD_INIT                 0            /* 昇降機の初期長さ       */
#define ROD_END_PRT            4.43            /* DCエンコの分解能          */

#define ROD_PERIOD_TIME              25             /* PIDの周期タイム           */

/* ##1度の移動時間は目検で調べるしかない */
#define ROD_MOVETIME     (   13 )			/* ROD 1 mm移動に必要な時間(ms)  */

/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言															  */
/* -------------------------------------------------------------------------- */
void msRODInit(void);
SLNG msRODGetBusy(UCHR* busyflags);
SLNG msRODSet(SLNG* returns, uint16_t* angles);
void msRODTimerCallback(void* id);

/* -------------------------------------------------------------------------- */
/* 構造体定義																  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */