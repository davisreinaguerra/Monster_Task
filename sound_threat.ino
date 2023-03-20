#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define SHIELD_RESET  -1        // VS1053 reset pin (unused!)
#define SHIELD_CS     7         // VS1053 chip select pin (output)
#define SHIELD_DCS    6         // VS1053 Data/command select pin (output)
#define CARDCS 4                // Card chip select pin
#define DREQ 3                  // VS1053 Data request, ideally an Interrupt pin

#define alignmentPin 8




// musicPlayer object
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {
  Serial.begin(9600);

  // Check for Connections
  if (!musicPlayer.begin()) {while (1);}
  Serial.println("Music Player found");
  if (!SD.begin(CARDCS)) {while (1);}
  Serial.println("SD Card found");
  
  // Set volume for (left, right) channels 
  musicPlayer.setVolume(40,40); // lower numbers == louder volume!

  while (Serial.available() == 0) {}     //wait for data available

}

void loop() {


  if(trig == LOW) {
    Serial.println("Waiting for trigger");
    digitalWrite(move_pin, LOW);

    // check for trigger
    trig = digitalRead(trig_pin);
  } 

  sound_and_alignment(alignmentPin);
  
}
  
void sound_and_alignment(int x) {
  digitalWrite(x,HIGH);
  musicPlayer.playFullFile("/GODZILLA.WAV");
  digitalWrite(x,LOW);
}
  
  
  
  
  /* Code for the random sound generator

  int randomN = random(0,100);
  Serial.println(randomN);
  bool play_sound = checkProb(sound_probability, randomN);
  if (play_sound) {
    sound_and_alignment(alignmentPin);
  } 
  else {
    delay(sound_duration);
  }

  */








/* Code for the random sound generator

bool checkProb(int x, int y) {
  if (y < x) {
    return true;
  } else {return false;}
}

void sound_and_alignment(int x) {
  digitalWrite(x,HIGH);
  musicPlayer.playFullFile("/PINK_N~1.WAV");
  digitalWrite(x,LOW);
}

*/
