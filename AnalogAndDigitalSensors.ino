int buttonPin = 5;
int redLed = 13;
int yellowLed = 9;
int ldrPin = A0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
}

void loop() {

  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(redLed, HIGH);
  } else {
    digitalWrite(redLed, LOW);
  }

  int sensorValue = analogRead(ldrPin);

int brightness = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(yellowLed, brightness);
}