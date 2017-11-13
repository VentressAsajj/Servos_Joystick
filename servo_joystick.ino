/*  @nuria_pp
 *  Referencias
 *    Armuino --- Funduino Joystick Shield ---
 *      Playlist: https://www.youtube.com/playlist?list=PLRFnGJH1nJiKIpz_ZyaU-uAZOkMH8GAcw
 *      Part 1. Introduction - Basic Functions: https://www.youtube.com/watch?v=lZPZuBCFMH4 
*/


/* Declaracion de librerias */

#include <Servo.h>

/* Creamos objeto los servos */
Servo servo1;
Servo servo2;

/* Definicion de constantes */
const int joyH = A1;          /* L/R  eje horizontal */
const int joyV = A0;          /* U/D eje vertical */

            
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
int valH = 90, valV = 90;     /* valor para servo horizontal y vertical */

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
  joyValueCompare(servoValue, valH);

  /* ajusta la posición del servo de acuerdo con el valor escalado */
  servo2.write(180 - valH);                  
  
  /* Lee el valor vertical de joystick entre 0 y 1023 */
  //servoVal = analogRead(joyV);

  servoValue = analogRead( PIN_ANALOG_Y );
  joyValueCompare(servoValue, valV);

  /* ajusta la posición del servo de acuerdo con el valor escalado */
  //servo1.write(180 - valV);                
  servo1.write(valV);

  delay(15);                                            

}

/*
 * Funcion outputJoystick muestra la posiciondel joystick por el serial
 */
/*
void outputJoystick(){

    Serial.print(analogRead(joyH));
    Serial.println ("----------------");
    Serial.print(analogRead(joyV));
    Serial.println ("----------------");
} // Fin_Funcion_outputJoystick
*/

/*
 * Funcion joyValueCompare
 *  Compara servoVal. Lee del joystick y actualiza el valor del eje dado
 */
void joyValueCompare(int servoVal, int &val){
  
  // foward
  if(servoVal > 1000 && val < 180)
    val += 10;
  else if(servoVal > 800 && val < 180)
    val += 5;
  else if(servoVal > 600 && val < 180)
    val += 2;
    
  // backward  
  if(servoVal < 20 && val > 0)
    val -= 10;
  else if(servoVal < 200 && val > 0)
    val -= 5;
  else if(servoVal < 400 && val > 0)
    val -= 2;
    
  if(val > 180){
    val = 180;
  }
  else if(val < 0){
    val = 0;
  }
} // Fin_Funcion_joyValueCompare
