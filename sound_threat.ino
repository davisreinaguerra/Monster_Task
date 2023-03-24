#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define SHIELD_RESET  -1        // VS1053 reset pin (unused!)
#define SHIELD_CS     7         // VS1053 chip select pin (output)
#define SHIELD_DCS    6         // VS1053 Data/command select pin (output)
#define CARDCS 4                // Card chip select pin
#define DREQ 3                  // VS1053 Data request, ideally an Interrupt pin


#define trig_pin 13


bool trig;




// musicPlayer object
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {
  Serial.begin(9600);

  pinMode(trig_pin, INPUT);
  
  // Check for Connections
  if (!musicPlayer.begin()) {while (1);}
  Serial.println("Music Player found");
  if (!SD.begin(CARDCS)) {while (1);}
  Serial.println("SD Card found");
  
  // Set volume for (left, right) channels 
  musicPlayer.setVolume(40,40); // lower numbers == louder volume!
}

void loop() {

  trig = digitalRead(trig_pin);

  if(trig == LOW) {
    Serial.println("Waiting");
  } 

  if(trig == HIGH) {
    Serial.println("Play that funky music");
    musicPlayer.playFullFile("/GODZILLA.WAV");
  }

  delay(50);
  
}
