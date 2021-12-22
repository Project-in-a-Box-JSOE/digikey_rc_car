//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BAUDRATE 9600
#define thumbstick_x A0
#define thumbstick_y A1

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

int raw_analog_reading_x, raw_analog_reading_y;

void setup() {
  
  Serial.begin(BAUDRATE);
  
  radio.begin();
  
  radio.openWritingPipe(address);
  
  radio.stopListening();
  
}

void send_joystick_inputs() {

  const int inputs[2] = {raw_analog_reading_x, raw_analog_reading_y};
  
  radio.write(&inputs, sizeof(inputs));

  delay(10);
  
}

void loop() {

  Serial.print("(X,Y)=");

  Serial.print("(");

  // Read + print thumbstick X
  raw_analog_reading_x = analogRead(thumbstick_x);
  Serial.print(raw_analog_reading_x);

  Serial.print(",");

  // Read + print thumbstick Y
  raw_analog_reading_y = analogRead(thumbstick_y);
  Serial.print(raw_analog_reading_y);

  Serial.println(")");

  send_joystick_inputs();
 
}
