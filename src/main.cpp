#include <Arduino.h>

// プロトタイプ宣言
void Straight(int, const int[]); // pwm, pin
void Back(int, const int[]);     // pwm, pin

// mode
#define frontMode 0
#define backMode 1
#define leftMode 2
#define rightMode 3
#define dirgonalMode 4

// オムニホイール //
// pin
const int omuni_motorPin_tate[4] = {}; // ! explain
const int omuni_motorPin_yoko[4] = {};
// mode
int omuni_moveMode = 0; // 移動のモード制御
// pwm
uint8_t omuni_pwmTate = 0;
uint8_t omuni_pwmYoko = 0;
uint8_t omuni_pwmDefault = 100;
// sizeof
const int omuni_motorPin_size = sizeof(omuni_motorPin_tate) / sizeof(omuni_motorPin_tate[0]);

void setup()
{
  // serial
  Serial.begin(115200);
  for (int i = 0; i < omuni_motorPin_size; i++)
  {
    pinMode(omuni_motorPin_tate[i], OUTPUT);
    pinMode(omuni_motorPin_yoko[i], OUTPUT);
  }
}

void loop()
{
  // ライントレースでモードを変更する。

  switch (omuni_moveMode)
  {
  case frontMode: // 前
    omuni_pwmTate = omuni_pwmDefault;
    Straight(omuni_pwmTate, omuni_motorPin_tate);
    break;
  case backMode: // 後ろ
    omuni_pwmTate = omuni_pwmDefault;
    Back(omuni_pwmTate, omuni_motorPin_tate);
    break;
  case rightMode: // 右
    omuni_pwmYoko = omuni_pwmDefault;
    Straight(omuni_pwmYoko, omuni_motorPin_yoko);
    break;
  case leftMode: // 左
    omuni_pwmYoko = omuni_pwmDefault;
    Back(omuni_pwmYoko, omuni_motorPin_yoko);
    break;
  default:
    omuni_pwmTate = 0;
    break;
  }
}

// pinの引数を変えると、縦横のオ  ムニを入れ替え可能！
// デメリット : モーター毎のpwm調整ができない <-結構致命的では？
// 直線
void Straight(int pwm, const int motorPin[]) // 2 motors * 2 = 4pins
{
  analogWrite(motorPin[0], pwm);
  analogWrite(motorPin[1], 0);
  analogWrite(motorPin[2], pwm);
  analogWrite(motorPin[3], 0);
}

// 直線と反対
void Back(int pwm, const int motorPin[]) // 4 pins
{
  analogWrite(motorPin[0], 0);
  analogWrite(motorPin[1], pwm);
  analogWrite(motorPin[2], 0);
  analogWrite(motorPin[3], pwm);
}

// 斜め
void Dirgonal(int pwm, int theta, int motorPin[]) // 8 pins
{
}

// 旋回
void Turn(int pwm, int motorPin[]) // 4 pins
{
}