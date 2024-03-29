/* -------------------------------------------------------------------------- */
/* hand.h																  */
/* ＣＬ２３・ＳＤ３２・ＲＤ４Ｃ												  */
/* HAND制御に係るヘッダ															  */
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
#define HAND_OK            (    0 )			    /* 成功						  */
#define HAND_NG            (   -1 )			    /* 失敗						  */
#define HAND_PARAM         (   -2 )			    /* 引数エラー				  */
#define HAND_READY         (    0 )			    /* HAND待機				  */
#define HAND_BUSY          (    3 )			    /* HANDビジー				  */
#define HAND_NOSET       ( 0xEFFF )			    /* HAND設定無し			  */
#define HAND_SPEED              4095            /* HANDモータの出力値              */

#define HAND_DST_MIN             0             /* HANDモータの最大距離          */
#define HAND_DST_MAX           270             /* HANDモータの最小角距離         */

#define HAND                      3            /* HANDのID                   */

#define HAND_PIN                  3            /* HANDのピン                */
#define HAND_DIR_PIN              9              /* HANDの方向ピン */

#define HAND_INIT                 0              /* HANDモータの初期ステータス */

#define HAND_PERIOD_TIME         25             /* PIDの周期タイム           */

/* ##1度の移動時間は目検で調べるしかない */
#define HAND_MOVETIME      (  2800)			/* HANDの移動に必要な時間(ms)  */

/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言															  */
/* -------------------------------------------------------------------------- */
void msHANDInit(void);
SLNG msHANDGetBusy(UCHR* busyflags);
SLNG msHANDSet(SLNG* returns, SSHT* angles);
void msHANDTimerCallback(void* id);

/* -------------------------------------------------------------------------- */
/* 構造体定義																  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */