/*  @nuria_pp
 *  Referencias
 *    Arduino --- Funduino Joystick Shield ---
 *      Playlist: https://www.youtube.com/playlist?list=PLRFnGJH1nJiKIpz_ZyaU-uAZOkMH8GAcw
 *      Part 1. Introduction - Basic Functions: https://www.youtube.com/watch?v=lZPZuBCFMH4 
 *  
 *  Nota: el control del joystick no es mio, siento no recordar de donde lo saque.
*/


/* Declaracion de librerias */

#include <Servo.h>

/* Creamos objeto los servos */
Servo servo1;
Servo servo2;

/* Definicion de constantes */
const int joystickH = A1;          /* L/R  eje horizontal */
const int joystickV = A0;          /* U/D eje vertical */

            
/* Asociamos los pines digitales del Arduino a los botones */
const byte PIN_BUTTON_A = 2; 
const byte PIN_BUTTON_B = 3;
const byte PIN_BUTTON_C = 4;
const byte PIN_BUTTON_D = 5;
const byte PIN_BUTTON_E = 6;
const byte PIN_BUTTON_F = 7;

/* Pins analogicos del Arduino asociados al joystick */
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

/* servoValue: leemos el valor del pin analogico */
int servoValue;                 
int valueH = 90, valueV = 90;     /* valor para servo horizontal y vertical */

void setup() {
  /* 
   *  selecionamos el pin 2 para el servo1
   *  selecionamos el pin 10 para el servo2
   */
  servo1.attach(2);  
  servo2.attach(10);
  Serial.begin(9600);
}


void loop() {
  /* funcion que muestra los valores del joystick por el monitor serie  */
  /*outputJoystick();*/

  /* Lectura de los valores horizontales del joystick (valores entre 0 and 1023) */  
  servoValue = analogRead( PIN_ANALOG_X );
  
  Serial.println(servoValue);
  joyValueCompare(servoValue, valueH);

  /* ajusta la posición del servo de acuerdo con el valor escalado */
  servo2.write(180 - valueH);                  
  
  /* Lee el valor vertical de joystick entre 0 y 1023 */
  //servoVal = analogRead(joystickV);

  servoValue = analogRead( PIN_ANALOG_Y );
  joyValueCompare(servoValue, valueV);

  /* ajusta la posición del servo de acuerdo con el valor escalado */
  //servo1.write(180 - valueV);                
  servo1.write(valueV);

  delay(15);                                            

}

/*
 * Funcion outputJoystick muestra la posiciondel joystick por el serial
 */
/*
void outputJoystick(){

    Serial.print(analogRead(joystickH));
    Serial.println ("----------------");
    Serial.print(analogRead(joystickV));
    Serial.println ("----------------");
} // Fin_Funcion_outputJoystick
*/

/*
 * Funcion joyValueCompare
 *  Compara servoVal. Lee del joystick y actualiza el valor del eje dado
 */
void joyValueCompare(int servoVal, int &value){
  
  // foward
  if(servoVal > 1000 && value < 180)
    value += 10;
  else if(servoVal > 800 && value < 180)
    value += 5;
  else if(servoVal > 600 && value < 180)
    value += 2;
    
  // backward  
  if(servoVal < 20 && value > 0)
    value -= 10;
  else if(servoVal < 200 && value > 0)
    value -= 5;
  else if(servoVal < 400 && value > 0)
    value -= 2;
    
  if(value > 180){
    value = 180;
  }
  else if(value < 0){
    value = 0;
  }
} // Fin_Funcion_joyValueCompare
