/*
 *****************************************************
 *   Variables Globales y estructuras
 *****************************************************
*/
#define RS 5 //PIN D19 o D5
#define EN 17 //PIN D18 o TX2 GPIO17
#define DB4 16 //PIN D5 o RX2 GPIO16
#define DB5 4 //PIN D4
#define DB6 2 //PIN D2
#define DB7 15 //PIN D15


LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7); //INICIALIZACION LCD 16x2
BluetoothSerial SerialBT; // Bluetooth Serial object

const int buttonPin = 27;     // el pin del botón 

int lastState = LOW;  // el estado anterior del pin de entrada
int currentState;   // la lectura actual del pin de entrada

// Maneja mensajes recibidos y enviados
String message = "";
char incomingChar;
