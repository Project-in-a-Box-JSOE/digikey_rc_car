// Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BAUDRATE 9600
#define CE 9
#define CSN 8

// Create an RF24 object
RF24 radio(CE, CSN);

// Unique address through which two modules communicate.
const byte address[6] = "00001";

void setup() {
  
  Serial.begin(BAUDRATE);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
  
}

void loop() {

  const int data_pair[2];
  
  //Read the data if available in buffer
  if(radio.available()) {
    radio.read(&data_pair, sizeof(data_pair));
  }

  Serial.print(data_pair[0]);
  Serial.print(",");
  Serial.println(data_pair[1]);
  
}
