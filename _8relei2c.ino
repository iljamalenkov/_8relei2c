// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)
char c;
int x=0;
int pin=0;

#include <Wire.h>

// подключаем библиотеку
#include <dht.h>

// создаём объект-сенсор
DHT sensor = DHT();

void setup() {
   Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
   Serial.begin(9600);
   
    // методом attach объявляем к какому контакту подключен
    // сенсор. В нашем примере это нулевой аналоговый контакт
    sensor.attach(A1);
    //
    // после подачи питания ждём секунду до готовности сенсора к работе
    delay(1000);
  // set the digital pin as output:
  pinMode(2, OUTPUT);
pinMode(3, OUTPUT);   
pinMode(4, OUTPUT);   
pinMode(5, OUTPUT);   
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);   
pinMode(10, OUTPUT);   
pinMode(9, OUTPUT);

 
}



void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
     if (Serial.available() > 0) {
char q={Serial.read()- '0'};
    if (q==49) {pin=2;}
    if (q==50) {pin=3;}
    if (q==51) {pin=4;}
    if (q==52) {pin=5;}
    if (q==53) {pin=6;}
    if (q==54) {pin=7;}
    if (q==55) {pin=9;}
    if (q==56) {pin=10;}
    if (q==1) {digitalWrite(pin, HIGH); Serial.print(pin); Serial.println(" on");}
    if (q==0) {digitalWrite(pin, LOW);  Serial.print(pin); Serial.println(" off");}
    }
   delay (100);
   
    // метод update заставляет сенсор выдать текущие измерения
    sensor.update();

    switch (sensor.getLastError())
    {
        case DHT_ERROR_OK:
            char msg[128];
            // данные последнего измерения можно считать соответствующими
            // методами
            sprintf(msg, "Temperature = %dC, Humidity = %d%%", 
                    sensor.getTemperatureInt(), sensor.getHumidityInt());
            Serial.println(msg);
            break;
        case DHT_ERROR_START_FAILED_1:
            Serial.println("Error: start failed (stage 1)");
            break;
        case DHT_ERROR_START_FAILED_2:
            Serial.println("Error: start failed (stage 2)");
            break;
        case DHT_ERROR_READ_TIMEOUT:
            Serial.println("Error: read timeout");
            break;
        case DHT_ERROR_CHECKSUM_FAILURE:
            Serial.println("Error: checksum error");
            break;
    }

    delay(3000);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
   c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
