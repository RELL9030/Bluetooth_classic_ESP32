/*
* Variables Globales y estructuras
*/

LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7); //INICIALIZACION LCD 16x2
BluetoothSerial SerialBT; // Bluetooth Serial object

const int buttonPin = 27;     // el pin del botón 

int lastState = LOW;  // el estado anterior del pin de entrada
int currentState;   // la lectura actual del pin de entrada

// Maneja mensajes recibidos y enviados
String message = "";
char incomingChar;
