const int switchPin = 5;   
const int ledPin = 13;    

void setup() {
  pinMode(switchPin, INPUT_PULLUP);  
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int touch = digitalRead(switchPin);

  if (touch == LOW) {        
    digitalWrite(ledPin, HIGH);  
  } else {                  
    digitalWrite(ledPin, LOW);  
  }
}