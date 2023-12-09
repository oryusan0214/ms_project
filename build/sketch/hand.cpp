#line 1 "C:\\WORK\\学校\\未来創造展\\ms_project\\ms_project\\hand.cpp"
/* -------------------------------------------------------------------------- */
/* hand.cpp																  */
/* HANDモーター制御に関わる処理												  */
/* 出力系はHANDと同じ処理方法で対応すると良い								  */
/* -------------------------------------------------------------------------- */
/* 番号		更新履歴								日付		氏名		  */
/* -------------------------------------------------------------------------- */
/* 000000	新規作成								2013/05/08	桝井　隆治	  */
/* 000001	機能追加								2023/12/06	筈尾　辰也		 */
/* -------------------------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS

/* -------------------------------------------------------------------------- */
/* includeファイル															  */
/* -------------------------------------------------------------------------- */
#include <stdio.h>								/* 基本的なＩ／Ｏ情報		  */
#include <string.h>								/* 初期化関連				  */
#include <stdarg.h>								/* システムログ				  */
#include <stdlib.h>								/* メモリ操作				  */
#include "time.h"								/* 時間に関するヘッダ		  */
#include "log.h"								/* ログに関わるヘッダ		  */
#include "hand.h"									/* HANDに関わるヘッダ		  */

/* -------------------------------------------------------------------------- */
/* プロトタイプ宣言(ローカル)												  */
/* -------------------------------------------------------------------------- */
void msHANDInitRecord(HAND_MNG* mng);

/* -------------------------------------------------------------------------- */
/* 構造体定義（ローカル）													  */
/* -------------------------------------------------------------------------- */
typedef struct {
	SLNG timerid;								/* タイマーID				  */
	UCHR busyflg;								/* ビジーフラグ(HAND個数分)	 */
	SSHT oldstate;							    /* 前回設定開閉情報たち 		  */
} HAND_MNG;

/* -------------------------------------------------------------------------- */
/* グローバル変数宣言														  */
/* -------------------------------------------------------------------------- */
HAND_MNG g_Mng;									/* HAND管理データ				  */

/* -------------------------------------------------------------------------- */
/* 関数名		：msHANDInit												  */
/* 機能名		：HANDモータの初期化処理										  */
/* 機能概要		：グローバル変数等の初期化を行います						  */
/* 引数			：void		: 無し											  */
/* 戻り値		：void		: 無し											  */
/* 作成日		：2013/03/12	桝井　隆治		新規作成					  */
/* -------------------------------------------------------------------------- */
void msHANDInit(void)
{
	msHANDInitRecord(&g_Mng);
	
	return;
}

/* -------------------------------------------------------------------------- */
/* 関数名		：msHANDInitRecord											  */
/* 機能名		：HANDモータの初期化処理(１レコード)							  */
/* 機能概要		：															  */
/* 引数			：void		: 無し											  */
/* 戻り値		：void		: 無し											  */
/* 作成日		：2013/03/12	桝井　隆治		新規作成					  */
/* -------------------------------------------------------------------------- */
void msHANDInitRecord(HAND_MNG* mng)
{
	if (mng == NULL) {
		msLog("これもう無理やで");
		return;
	}
	/* １レコード初期化 */
	mng->timerid = 0;
	mng->busyflg = MS_HAND_READY;
	mng->oldstate = 0;
	return;
}

/* -------------------------------------------------------------------------- */
/* 関数名		：msHANDGetBusy											  */
/* 機能名		：HANDビジー状態取得										  */
/* 機能概要		：現在のHANDモーターが動作中か否かを返却します。			  */
/*				：本開発でのHANDは1個固定なので、引数データも1個用意する事	*/
/* 引数			：UCHR*		: busyflags	 ：[OUT] フラグ(1個のみ動作)		  */
/* 戻り値		：SLNG		: MS_HAND_OK	：正常終了						  */
/*				：			: MS_HAND_PARAM：引数異常						  */
/* 作成日		：2013/03/12	桝井　隆治		新規作成					  */
/* -------------------------------------------------------------------------- */
SLNG msHANDGetBusy(UCHR* busyflags)
{
	/* 引数チェック(OnjectはNULLを許可する)---------------------------------- */
	if (busyflags == NULL) {
		msLog("引数エラー");
		return MS_HAND_PARAM;
	}

	/* ビジーデータコピーして返却 */
	*busyflags = g_Mng.busyflg;

	return MS_HAND_OK;
}

/* -------------------------------------------------------------------------- */
/* 関数名		：msHANDGetSet												  */
/* 機能名		：HAND角度設定												  */
/* 機能概要		：HANDモーターの角度設定を行います。							  */
/*	##			：１度角度を移動するのに〇〇秒要すると定義し、現在の角度に対し*/
/*				：相対移動量×〇〇秒でタイマーをセットし、管理する。		  */
/*				：busyフラグが立っている所は設定せず、それ以外のみ設定する。  */
/*				：事前に必ず仕様を良く理解して使う事。						  */
/* 引数			：SLNG*		: returns	 ：[OUT] 各HANDの設定が完了可否		  */
/*				：			:			 ： MS_HAND_OK    :設定成功		  */
/*				：			:			 ： MS_HAND_BUSY  :ビジーの為失敗    */
/*				：			:			 ： MS_HAND_PARAM :角度がおかしい    */
/*				：bool		: setting	 ：[I N] 各HANDの設定   			  */
/*				：			:			 ：何もしない場合はMS_HAND_NOSET	  */
/* 戻り値		：SLNG		: MS_HAND_OK	：正常終了						  */
/*				：			: MS_HAND_PARAM：引数異常						  */
/* ■■注意■■ ：正常終了を返しても、第一引数のreturnsはエラーの場合がある為 */
/*				：必ずチェックする事！										  */
/* 作成日		：2013/03/12	桝井　隆治		新規作成					  */
/* -------------------------------------------------------------------------- */
SLNG msHANDSet(SLNG* returns, bool setting)
{
	SLNG handRet = MS_HAND_OK;

	/* 引数チェック(OnjectはNULLを許可する)---------------------------------- */
	if (returns == NULL) {
		msLog("引数エラー");
		return MS_HAND_PARAM;
	}

	/* HANDがビジー時は上位層の設定ミス */
	if (g_Mng.busyflg == MS_HAND_BUSY) {
		*returns = MS_HAND_BUSY;
		continue;
	}
	/* ##要確認：HANDの角度範囲がおかしい場合はパラメータエラー */
	if ((setting <false) || (true < setting) && (setting != MS_HAND_NOSET)) {
		*returns = MS_HAND_PARAM;
		continue;
	}
	/* HANDモーター設定可能と判断 --------------------------------------*/


	/* 指定角度からHAND移動に必要な時間を算出 */
	UINT_8 handUD = 0;  					/* 回転方向を判断する				 */
											/* 初期は逆転(マイナス方向)			 */

    /* 開閉方向判断 */
    if(g_Mng.oldangles == setting){
        handUD = 0;
    }elseif(g_Mng.oldstate < setting){
        handUD = 1;
    }else{
        handUD = 2;
    }
	/* タイマー計算＆コールバック設定 */
	handRet = msSetTimer(MS_HAND_MOVETIME, &g_Mng, msHANDTimerCallback);
	if ((handRet == MS_TIME_FULL) || (handRet == MS_TIME_PARAM)) {
		msLog("タイマー関連エラー: %d", handRet);
		return MS_HAND_NG;
	}
	/* タイマーIDを保管 */
	g_Mng.timerid = handRet;

	/* 指定角度を古くしておく */
	g_Mng.oldangles = setting;

	/* ##HANDモーターのレジスタ設定 */
	if(handUD == 0) {
		analogWrite(MS_HAND_PIN, 0);
	}else if(handUD == 1){
		analogWrite(MS_HAND_PIN, MS_HAND_SPEED);
	}else{
        analogWrite(MS_HAND_PIN, -MS_HAND_SPEED);
    }
	/* 必要ならディレイ */
  	// delay(1);
	
	return MS_HAND_OK;
}
/* -------------------------------------------------------------------------- */
/* 				Copyright HAL College of Technology & Design				  */
/* -------------------------------------------------------------------------- */