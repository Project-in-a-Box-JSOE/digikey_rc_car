#define BAUDRATE 9600

// Motor pinout
#define enA 6
#define in1 7
#define in2 5

// Pin out for one thumbstick
#define thumbstick_y A0

int raw_analog_reading_y;

void setup() {

  Serial.begin(BAUDRATE);
  
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

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

  Serial.print("(Y)=");

  Serial.print("(");

  // Read + print thumbstick Y
  raw_analog_reading_y = analogRead(thumbstick_y);
  Serial.print(raw_analog_reading_y);

  Serial.println(")");

  map_motomoto();
  
}
