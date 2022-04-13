//FUNCTIONS


// GPIO where LED is connected to 
//RGB Anodo comun(+): 32,33,25 Catodo comun(-): 25,33,32
//BICOLOR: RED:25 BLUE:33 
const int ledPinR=25, ledPinG=32, ledPinB=33;

void setColor(int R, int G, int B) {
  digitalWrite(ledPinR, R);
  digitalWrite(ledPinG, G);
  digitalWrite(ledPinB, B);
}
