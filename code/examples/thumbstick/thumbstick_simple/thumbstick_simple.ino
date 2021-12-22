#define BAUDRATE 9600

// Pin out for two thumbsticks
#define thumbstick_x A0
#define thumbstick_y A1

int raw_analog_reading_x, raw_analog_reading_y;

void setup() {

  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

}

// Continuously print the X and Y analog readings 
// and the state of the push-button of the thumbstick

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

  delay(10);

}
