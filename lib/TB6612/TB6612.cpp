#include "TB6612.h"

TB6612::TB6612(int AIN1, int AIN2, int BIN1, int BIN2, int PWMA, int PWMB, int STBY)
{

  // Inicializa el objeto con una distribución de patas libre
  _AIN1 = AIN1;
  _AIN2 = AIN2;
  _BIN1 = BIN1;
  _BIN2 = BIN2;
  _PWMA = PWMA;
  _PWMB = PWMB;
  _STBY = STBY;

  pinMode(_AIN1, OUTPUT);
  pinMode(_AIN2, OUTPUT);
  pinMode(_BIN1, OUTPUT);
  pinMode(_BIN2, OUTPUT);
  //pinMode(_PWMA, OUTPUT);
  //pinMode(_PWMB, OUTPUT);
  pinMode(_STBY, OUTPUT);
}

void TB6612::forward(int velocidad_L, int velocidad_R, int tiempo)
{
  digitalWrite(_STBY, HIGH);

  digitalWrite(_AIN1, LOW);
  digitalWrite(_AIN2, HIGH);
  analogWrite(_PWMA, constrain (velocidad_L, 0, ANALOG_W_RES));

  digitalWrite(_BIN1, LOW);
  digitalWrite(_BIN2, HIGH);
  analogWrite(_PWMB, constrain (velocidad_R, 0, ANALOG_W_RES));

  if (tiempo != 0){
    delay (abs (tiempo));
    brake (0);

  }
}

void TB6612::reverse(int velocidad_L, int velocidad_R, int tiempo)
{
  digitalWrite(_STBY, HIGH);

  digitalWrite(_AIN1, HIGH);
  digitalWrite(_AIN2, LOW);
  analogWrite(_PWMA, constrain (velocidad_L, 0, ANALOG_W_RES));

  digitalWrite(_BIN1, HIGH);
  digitalWrite(_BIN2, LOW);
  analogWrite(_PWMB, constrain (velocidad_R, 0, ANALOG_W_RES));

  if (tiempo != 0){
    delay (abs (tiempo));
    brake (0);

  }
}

void TB6612::coast(int tiempo)
{
   digitalWrite(_STBY, LOW);

  digitalWrite(_AIN1, LOW);
  digitalWrite(_AIN2, LOW);
  analogWrite(_PWMA, 0);

  digitalWrite(_BIN1, LOW);
  digitalWrite(_BIN2, LOW);
  analogWrite(_PWMB, 0);
  if (tiempo != 0){
    delay (abs (tiempo));
  }

}

void TB6612::brake(int tiempo)
{
   digitalWrite(_STBY, HIGH);

  digitalWrite(_AIN1, HIGH);
  digitalWrite(_AIN2, HIGH);
  analogWrite(_PWMA, ANALOG_W_RES);

  digitalWrite(_BIN1, HIGH);
  digitalWrite(_BIN2, HIGH);
  analogWrite(_PWMB, ANALOG_W_RES);
  if (tiempo != 0){
    delay (abs (tiempo));
  }

}

void TB6612::rotate(int velocidad, int tiempo)
{
  digitalWrite(_STBY, HIGH);

  analogWrite(_PWMA, constrain (velocidad, 0, ANALOG_W_RES));
  analogWrite(_PWMB, constrain (velocidad, 0, ANALOG_W_RES));

  if (tiempo > 0) {
    digitalWrite(_AIN1, LOW);
    digitalWrite(_AIN2, HIGH);
    digitalWrite(_BIN1, HIGH);
    digitalWrite(_BIN2, LOW);
  }
  else
  {
    digitalWrite(_AIN1, HIGH);
    digitalWrite(_AIN2, LOW);
    digitalWrite(_BIN1, LOW);
    digitalWrite(_BIN2, HIGH);
  }

  if (tiempo != 0){
    delay (abs (tiempo));
    brake (0);

  }

}

void TB6612::setSpeed(int speed, int motor)
{
  digitalWrite(_STBY, HIGH);

  if ((motor == 0)||(motor == 2)){
    if (speed>0){
      digitalWrite(_AIN1, LOW);
      digitalWrite(_AIN2, HIGH);
      analogWrite(_PWMA, constrain (speed, 0, ANALOG_W_RES));
    }else{
      digitalWrite(_AIN1, HIGH);
      digitalWrite(_AIN2, LOW);
      analogWrite(_PWMA, constrain (-speed, 0, ANALOG_W_RES));
    }
  }
  if ((motor == 1)||(motor == 2)){
    if (speed>0){
      digitalWrite(_BIN1, LOW);
      digitalWrite(_BIN2, HIGH);
      analogWrite(_PWMB, constrain (speed, 0, ANALOG_W_RES));
    }else{
      digitalWrite(_BIN1, HIGH);
      digitalWrite(_BIN2, LOW);
      analogWrite(_PWMB, constrain (-speed, 0, ANALOG_W_RES));

    }
  }


}