/*
 * Date:    13/03/2022
 * Title:   LCD + Bluetooth + RGB
 * Author:  Rubén Lozano
 * 
 * References: 
 *              
*/

/*
 *****************************************************
 *    LIBRERIAS
 *****************************************************
*/
#include <LiquidCrystal.h>  
#include "BluetoothSerial.h"
#include "Funciones.h"

/*
 *****************************************************
 *    VARIABLES DEFINIDAS.
 *****************************************************
*/
#define RS 5 //PIN D19 o D5
#define EN 17 //PIN D18 o TX2 GPIO17
#define DB4 16 //PIN D5 o RX2 GPIO16
#define DB5 4 //PIN D4
#define DB6 2 //PIN D2
#define DB7 15 //PIN D15

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7); //INICIALIZACION LCD 16x2
BluetoothSerial SerialBT; // Bluetooth Serial object

const int buttonPin = 27;     // el pin del botón 

// variables will change:
int lastState = LOW;  // el estado anterior del pin de entrada
int currentState;   // la lectura actual del pin de entrada

// Handle received and sent messages
String message = "";
char incomingChar;

/*
 *****************************************************
 *    SETUP
 *****************************************************
*/
void setup()
{
  Serial.begin(115200);
 
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);// the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  
  lcd.begin(16, 2);         //Inicialización de la pantalla LCD 16x2.
  lcd.clear();              //Limpieza de pantalla
  lcd.setCursor(3, 0);      //Posición del cursor (F,C)
  lcd.print("Bienvenido");  //Impresión de mensaje inicial
  
  lcd.setCursor(0, 1);
  //lcd.setCursor(16, 1);
  //lcd.autoscroll();// set the display to automatically scroll:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print("...");
    delay(500);
  }
  SerialBT.begin("ESP32");  // Bluetooth device name
  Serial.println("El dispositivo comenzó, ahora puedes emparejarlo con bluetooth!");
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("BT INICIADO"); 
  delay(100);
}

/*
 *****************************************************
 *    LOOP
 *****************************************************
 */
void loop(){
    currentState = digitalRead(buttonPin);// Lee el valor del estado del botón
  
  // Lee los mensajes recibidos desde la aplicación del monitor serial
  if (Serial.available()) {
        char serialChar = Serial.read();
    if (serialChar != '\n'){
      message += String(serialChar);
    }
    else{
      message = "";
    }
      SerialBT.write(serialChar);
  }

    // Lee mensajes recibidos desde una aplicación BT externa (APP EN ANDROID)
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar); 
  }
  
  // Verifica el mensaje recibido y controla la salida en consecuencia
  if (message =="led_on" || (lastState == HIGH && currentState == LOW)){
    Serial.println("\n Botón presionado");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    
    // color code #00C9CC (R = 0,   G = 201, B = 204)
    setColor( 0, 201, 204);
    delay(1000); // mantener el color 1 segundo
  
    // color code #F7788A (R = 247, G = 120, B = 138)
    setColor( 247,120, 138);  
    delay(1000); 
  
    // color code #34A853 (R = 52,  G = 168, B = 83)
    setColor( 52, 168, 83);
    delay(1000);

    // color code #ff009f (R = 240,  G = 0, B = 10)
    setColor( 240, 0, 10);
    delay(1000);
  }
  else if (message =="led_off" || (lastState == LOW && currentState == HIGH)){
    Serial.println(" \n Botón no presionado");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    setColor(0,0,0);
  }
     
    lastState = currentState; // Guarda el último estado del botón
  delay(20);

}
