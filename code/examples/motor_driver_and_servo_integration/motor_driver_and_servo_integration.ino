// Import Arudino's Servo library
#include <Servo.h>

#define BAUDRATE 9600

// Pin out for two thumbsticks
#define thumbstick_x A0
#define thumbstick_y A1

// Motor pinout
#define enA 6
#define in1 7
#define in2 5

// Sero pinout
#define servo_pin 10

Servo servo;

int raw_analog_reading_x, raw_analog_reading_y;

void setup() {

  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

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

void map_servo() {

  // Tweak joystick min and max mapped values as necessary
  int servo_pos = map(raw_analog_reading_x, 0, 681, 0, 180);
  
  servo.write(servo_pos);
  
}

void map_motomoto() {

  int motor_speed = 255;  // Feel free to tweak. For PWM maximum possible values are 0 to 255

  if(raw_analog_reading_y > 352){
    // Forward. Tweak threshold to +5 of middle/rest state analog reading
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if(raw_analog_reading_y < 342){
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

  map_servo();

  map_motomoto();
  
}
