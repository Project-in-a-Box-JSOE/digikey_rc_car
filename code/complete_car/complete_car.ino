//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define BAUDRATE 9600
#define CE 9
#define CSN 8

// Motor pinout
#define enA 6
#define in1 7
#define in2 5

// Servo pinout
#define servo_pin 10

// Create an RF24 object
RF24 radio(CE, CSN);

// Create servo object
Servo servo;

// Unique address through which two modules communicate.
const byte address[6] = "00001";

int raw_analog_reading_x, raw_analog_reading_y;

void setup() {

  Serial.begin(BAUDRATE);

  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Attach servo pin to Servo object
  servo.attach(servo_pin);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
}

// Receives the x and y inputs from the remote
void receive_thumbstick_inputs() {

  const int inputs[2];

  // Read the data if available in buffer
  if(radio.available()) {
    radio.read(&inputs, sizeof(inputs));
  }

  // Refresh current joystick input readings
  raw_analog_reading_x = inputs[0];
  raw_analog_reading_y = inputs[1];
  
}

// Maps current reading of x thumbstick to servo arm
void map_servo() {

  // Tweak joystick min and max mapped values as necessary
  int servo_pos = map(raw_analog_reading_x, 0, 686, 0, 180);
  
  servo.write(servo_pos);
  
}

// Maps current reading of y thumbstick to motor
void map_motomoto() {

  int motor_speed = 255;  // Feel free to tweak. For PWM maximum possible values are 0 to 255

  if(raw_analog_reading_y > 357){
    // Forward. Tweak threshold to +5 of middle/rest state analog reading
    digitalWrite(in1, HIGH);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if(raw_analog_reading_y < 347){
    // Backward. Tweak threshold to -5 of middle/rest state analog reading
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else { 
    // Stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
  
  analogWrite(enA, motor_speed);
  
}

void loop() {

  receive_thumbstick_inputs();
  
  map_servo();

  map_motomoto();
/*
  Serial.print("(X,Y)=(");
  Serial.print(raw_analog_reading_x);
  Serial.print(",");
  Serial.print(raw_analog_reading_y);
  Serial.println(")");
  */
   
}
