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
 *
 *    LIBRERIAS
 *
 *****************************************************
*/
#include <LiquidCrystal.h>  
#include "BluetoothSerial.h"
#include "Funciones.h"
/*
 *****************************************************
 *
 *    VARIABLES DEFINIDAS.
 *
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

const int buttonPin = 27;     // the number of the pushbutton pin 27;

// variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;   // the current reading from the input pin

// Handle received and sent messages
String message = "";
char incomingChar;

// Timer: auxiliar variables
unsigned long previousMillis = 0;    // Stores last time temperature was published
const long interval = 10000;         // interval at which to publish sensor readings

/*
 *****************************************************
 *
 *    SETUP
 *
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
  Serial.println("The device started, now you can pair it with bluetooth!");
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("BT INICIADO"); 
  delay(100);
}

/*
 *****************************************************
 *
 *    LOOP
 *
 *****************************************************
 */
void loop(){
  // read the state of the pushbutton value:
  currentState = digitalRead(buttonPin);
   unsigned long currentMillis = millis();
  // Send temperature readings
 /* if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    sensors.requestTemperatures(); 
    temperatureString = String(sensors.getTempCByIndex(0)) + "C  " +  String(sensors.getTempFByIndex(0)) + "F";
    SerialBT.println(temperatureString); 
  }*/

 // Read received messages form serial monitor aplication (LED control command)
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

    // Read received messages form external BT aplication (LED control command)
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
  
  // Check received message and control output accordingly
  if (message =="led_on" || (lastState == HIGH && currentState == LOW)){
    Serial.println("\n The button is pressed");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    /*lcd.setCursor(0, 1);
    lcd.print();*/
    
    /*digitalWrite(ledPinR, HIGH);
    digitalWrite(ledPinG, HIGH);*/
    //digitalWrite(ledPinB, HIGH);
    
    // color code #00C9CC (R = 0,   G = 201, B = 204)
    setColor( 242, 211, 70);
    delay(1000); // keep the color 1 second
  
    // color code #F7788A (R = 247, G = 120, B = 138)
    setColor( 0, 0, 251);  
    delay(1000); // keep the color 1 second
  
    // color code #34A853 (R = 52,  G = 168, B = 83)
    setColor( 251, 0, 0);
    delay(1000); // keep the color 1 second

    // color code #ff009f (R = 240,  G = 0, B = 10)
    setColor( 207, 99, 135);
    delay(1000); // keep the color 1 second
  }
  else if (message =="led_off" || (lastState == LOW && currentState == HIGH)){
    Serial.println(" \n The button is released");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);

  }
     
    lastState = currentState; // save the the last state
  delay(20);

}
