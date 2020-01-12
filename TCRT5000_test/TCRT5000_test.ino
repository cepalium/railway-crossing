/*
  Inspired by AnalogInOutSerial, an example of Arduino
*/

// These constants won't change. They're used to give names to the pins used:
const int irInput = A4;  // Analog input pin that TCRT5000 is attached to
const int ledPin = 13; // Digital output pin that the LED is attached to

int irValue;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(irInput, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the analog in value:
  irValue = analogRead(irInput);

  if(irValue < 512) {
    digitalWrite(ledPin, HIGH);
    }
  else {
    digitalWrite(ledPin, LOW);
    }

  // print the results to the Serial Monitor:
  Serial.print("IR = ");
  Serial.println(irValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}
