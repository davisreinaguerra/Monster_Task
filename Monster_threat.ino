#define move_pin 10 // white wire
#define enable_pin 7 // blue wire
#define trig_pin 12

bool trig;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(move_pin, OUTPUT);
  pinMode(enable_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  trig = digitalRead(trig_pin);

  Serial.print("Trig state is: ");
  Serial.println(trig);

  if (trig == 0) {
    Serial.println("Waiting for trigger");
    digitalWrite(enable_pin, LOW);
  }
  
  if (trig == 1) {
    digitalWrite(enable_pin, HIGH);
    Serial.println("monster triggered");

    //move monster
    digitalWrite(move_pin, HIGH);
    delay(500);
    digitalWrite(move_pin, LOW);
    delay(500);

  }

  delay(50);
}
