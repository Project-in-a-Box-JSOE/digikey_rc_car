// Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE 9
#define CSN 8

// Create an RF24 object
RF24 radio(CE, CSN);

// Unique address through which two modules communicate.
const byte address[6] = "00001";

void setup() {
  
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
  
}

void loop() {

  const int data_pair[2] = {772, 523};
  
  radio.write(&data_pair, sizeof(data_pair));
  
  delay(1000);
  
}
