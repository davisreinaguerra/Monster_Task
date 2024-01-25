//_______________ Door Servo Setup _________________
#include <Servo.h>
Servo doorServo;
#define door_open_pos 60
#define door_closed_pos 160
#define door_pin 5
#define close_jitter 1000
#define open_close_delay 2000

void setup() {
  // put your setup code here, to run once:
  doorServo.attach(door_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  fast_open();
  delay(open_close_delay);
  fast_close_with_jitter();
  delay(open_close_delay);
}

void fast_open() {
  doorServo.write(door_open_pos);
}

void fast_close_with_jitter() {
  doorServo.write(door_closed_pos - 30);
  delay(close_jitter);
  doorServo.write(door_closed_pos);
}
