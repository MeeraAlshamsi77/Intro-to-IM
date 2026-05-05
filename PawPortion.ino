#include <Servo.h>

// these constants store the pin numbers so i don’t use random numbers.
const int SENSOR_PIN = 7;
const int SERVO_PIN  = 6;

// this creates the servo object that controls the food door.
Servo tap_servo;

// this controls how long arduino waits before allowing another feed.
// without this, the IR sensor could trigger repeatedly if something stays in front of it.
const unsigned long COOLDOWN_MS = 4000;

// these variables track the feeding state.
unsigned long lastFedTime = 0;
bool isDispensing = false;

// feeding function
void dispenseFood() {

  // this becomes true while feeding is happening,
  // so the code doesn’t trigger another feed at the same time.
  isDispensing = true;

  // this opens the servo to release food, waits, then closes it again.
  tap_servo.write(110);
  delay(2000);
  tap_servo.write(0);
  delay(300);

  // this saves when the last feeding happened.
  // it is used for the cooldown check later.
  lastFedTime = millis();
  isDispensing = false;

  // this tells p5 that feeding finished,
  // so it can update the pet mood and dashboard.
  Serial.println("DONE");
}

// setup
void setup() {

  // this starts serial communication so p5 and arduino can talk.
  Serial.begin(9600);

  // this sets the IR sensor as input because we read from it.
  pinMode(SENSOR_PIN, INPUT);

  // this attaches the servo and starts it in the closed position.
  tap_servo.attach(SERVO_PIN);
  tap_servo.write(0);
}

// loop
void loop() {

  // this checks if p5 sent a command through serial.
  // if the command is "FEED", arduino dispenses food immediately.
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "FEED") {
      dispenseFood();
    }
  }

  // this checks the IR sensor only when not already feeding.
  if (!isDispensing) {

    unsigned long now = millis();

    // this checks if enough time passed since the last feeding.
    bool cooldownOver = (now - lastFedTime) >= COOLDOWN_MS;

    if (cooldownOver) {

      int sensorVal = digitalRead(SENSOR_PIN);

      // for this sensor, 0 means something is detected.
      // when detected, feeding starts automatically.
      if (sensorVal == 0) {
        dispenseFood();
      }
    }
  }
}
