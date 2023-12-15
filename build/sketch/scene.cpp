#line 1 "C:\\WORK\\学校\\未来創造展\\ms_project\\ms_project\\scene.cpp"
/* Scene.run---------------------------------------------------------------- */
/*  1シーンを実行する */

/*  */

/* ------------------------------------------------------------------------- */
#include "scene.h"
#include "servo.h"
#include "dc.h"
#include "hand.h"
#include "rod.h"
#include "log.h"
#include <string.h>


/* Scene.judge */
/* シーンを更新するかを判断すする */

int sceneInuput(Scene *scene){
  Scene inputscene[]={
  /* --- ここからシーンを動かしていくこと ---*/
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  scene = inputscene;
  return sizeof(inputscene)/sizeof(inputscene[0]);
}

int sceneBusy(){
  uint8_t handbusy=0;
  uint8_t elevatorbusy=0;
  uint8_t armbusy[2]={0,0};
  uint8_t legbusy[SERVO_NUM]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int count = 0;

  msServoGetBusy(legbusy,sizeof(legbusy)/sizeof(legbusy[0]));
  msDCGetBusy(armbusy,sizeof(armbusy)/sizeof(armbusy[0]));
  msRODGetBusy(elevatorbusy);
  msHANDGetBusy(handbusy);

  if(
      handbusy==0 && 
      elevatorbusy==0 && 
      armbusy[0]==0 && armbusy[1]==0 && 
      legbusy[0]==0 && legbusy[1]==0 && legbusy[2]==0 && legbusy[3]==0 && legbusy[4]==0 && legbusy[5]==0 && legbusy[6]==0 && legbusy[7]==0 && legbusy[8]==0 && legbusy[9]==0 && legbusy[10]==0 && legbusy[11]==0 && legbusy[12]==0 && legbusy[13]==0 && legbusy[14]==0 && legbusy[15]==0 && legbusy[16]==0 && legbusy[17]==0
    ){
    return SCENE_OK;
  }
  else{
    return SCENE_NG;
  }
}
int scene(){
  static uint16_t scenecounter = 0;
  int returnvalue = 0;
  int sceneNext = SCENE_NG;
  uint16_t scene_num = 0;
  Scene *scene;

  uint16_t angle[SERVO_NUM]=        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint16_t arm[ARM_NUM] =           {0,0};
  uint16_t elevator[ELEVATOR_NUM] = {0};
  uint16_t handopen[HANDOPEN_NUM] = {0};

  
  sceneNext = sceneBusy();//モータが動いている状態かを判断
  if (scene_num == 0)
  {
    Serial.println("WARNING --- NON SCENE ---\n");
    
    return SCENE_END;
  }
  
  if (sceneNext == SCENE_OK)
  {
    if (scene_num <= scenecounter)
    {
      return SCENE_END;
    }
    
    Serial.println("--- scene ---\n");
    
    Serial.println("--now couter  --");
    
    Serial.println(scenecounter);
    
    scene_num=sceneInuput(scene);//シーンデータの取り込み
    //memcpy(angle,&scene[scenecounter],sizeof(angle)/sizeof(angle[0]));//servodataを抽出
    angle[0] =  scene[scenecounter].lf_neemotor;            //servodataを抽出
    angle[1] =  scene[scenecounter].lf_yaw_hipjointmotor;   //servodataを抽出
    angle[2] =  scene[scenecounter].lf_pitch_hipjointmotor; //servodataを抽出
    angle[3] =  scene[scenecounter].lc_neemotor;            //servodataを抽出
    angle[4] =  scene[scenecounter].lc_yaw_hipjointmotor;   //servodataを抽出
    angle[5] =  scene[scenecounter].lc_pitch_hipjointmotor; //servodataを抽出
    angle[6] =  scene[scenecounter].lb_kneemotor;           //servodataを抽出
    angle[7] =  scene[scenecounter].lb_yaw_hipjointmotor;   //servodataを抽出
    angle[8] =  scene[scenecounter].lb_pitch_hipjointmotor; //servodataを抽出
    angle[9] =  scene[scenecounter].rf_neemotor;            //servodataを抽出
    angle[10] = scene[scenecounter].rf_yaw_hipjointmotor;   //servodataを抽出
    angle[11] = scene[scenecounter].rf_pitch_hipjointmotor; //servodataを抽出
    angle[12] = scene[scenecounter].rc_neemotor;            //servodataを抽出
    angle[13] = scene[scenecounter].rc_yaw_hipjointmotor;   //servodataを抽出
    angle[14] = scene[scenecounter].rc_pitch_hipjointmotor; //servodataを抽出
    angle[15] = scene[scenecounter].rb_kneemotor;           //servodataを抽出
    angle[16] = scene[scenecounter].rb_yaw_hipjointmotor;   //servodataを抽出
    angle[17] = scene[scenecounter].rb_pitch_hipjointmotor; //servodataを抽出

    //memcpy(arm,scene[scenecounter].l_armmotor,sizeof(arm)/sizeof(arm[0]));
    arm[0]=scene[scenecounter].l_armmotor;                  //armdataを抽出
    arm[1]=scene[scenecounter].r_armmotor;                  //armdataを抽出

    elevator[0]=scene[scenecounter].elevator;                  //elevatordataを抽出

    handopen[0]=scene[scenecounter].hand;                      //handopendataを抽出
    msServoSet(returnvalue,angle,SERVO_NUM);//サーボに指令とエンコーダがないためbusy時間の設定
    msDCSet   (returnvalue,arm,ARM_NUM);//アームに指令
    msRODSet  (returnvalue,elevator);//昇降機に指令
    msHANDSet (returnvalue,handopen);//ハンド開閉に指令とエンコーダがないためbusy時間の設定
    Serial.println(scenecounter);
    delay(1);
    scenecounter = scenecounter + 1;//次のシーンに移る
    return SCENE_OK;
  }
  else if (sceneNext == SCENE_NG)
  {
    Serial.println("--- sceneBusy() ---\n");
    
    return SCENE_NG;
  }
  

}
