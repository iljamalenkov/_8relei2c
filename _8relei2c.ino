// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
int tt=0;
// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)
char c;
int x=0;
int pin=0;
#include <EEPROM.h>
boolean pstat[8];
byte pnum[8]={2,3,4,5,6,9,10,11};
// the current address in the EEPROM (i.e. which byte
// we're going to write to next)

#include <Wire.h>
const byte MY_ADDRESS = 42;
const byte OTHER_ADDRESS = 25;

void setup() {

   Serial.begin(9600);
   Wire.begin (MY_ADDRESS);
 
  Wire.onReceive (receiveEvent); 
    
  // set the digital pin as output:
 
   for (int ii = 0; ii<=8; ii++)
   {
     pinMode(pnum[ii], OUTPUT);
     if (EEPROM.read(ii) >> 0) digitalWrite(pnum[ii], HIGH); else digitalWrite(pnum[ii], LOW);
    }


}

void loop()
{
 serialRead();
   delay (10);
   
   
    if (tt>500) tt=0;
   
tt++;
    
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while (Wire.available () > 0)
  {byte c;
   c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    if (c=='a') {pin=0;}
    if (c=='b') {pin=1;}
    if (c=='c') {pin=2;}
    if (c=='d') {pin=3;}
    if (c=='e') {pin=4;}
    if (c=='f') {pin=5;}
    if (c=='g') {pin=6;}
    if (c=='h') {pin=7;}
    if (c=='1') {digitalWrite(pnum[pin], HIGH); EEPROM.write(pin,1); Serial.print(pin); Serial.println(" on");}
    if (c=='0') {digitalWrite(pnum[pin], LOW);  EEPROM.write(pin,0); Serial.print(pin); Serial.println(" off");}
  }
  
}

    void serialRead(){
       if (Serial.available() > 0) {
char q={Serial.read()- '0'};
    if (q==49) {pin=0;}
    if (q==50) {pin=1;}
    if (q==51) {pin=2;}
    if (q==52) {pin=3;}
    if (q==53) {pin=4;}
    if (q==54) {pin=5;}
    if (q==55) {pin=6;}
    if (q==56) {pin=7;}
    if (q==1) {digitalWrite(pnum[pin], HIGH); EEPROM.write(pin,1);Serial.print(pin); Serial.println(" on");}
    if (q==0) {digitalWrite(pnum[pin], LOW);  EEPROM.write(pin,0);Serial.print(pin); Serial.println(" off");}
    }}
    // function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write("hello "); // respond with message of 6 bytes
                       // as expected by master
}
