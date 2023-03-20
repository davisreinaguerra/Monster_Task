// Adafruit protomatter definition
#include <Adafruit_Protomatter.h>
// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

uint8_t rgbPins[]  = {7, 8, 9, 10, 11, 12};
uint8_t addrPins[] = {17, 18, 19, 20};
uint8_t clockPin   = 14;
uint8_t latchPin   = 15;
uint8_t oePin      = 16;

// adafruit LED matrix object
Adafruit_Protomatter matrix(
  32, 4, 1, rgbPins, 4, addrPins, clockPin, latchPin, oePin, false);

// Looming specific global vars
#define trig_pin 25 //A3
#define delayTime 50
bool trig;

void setup(void) {
  Serial.begin(9600);

  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if(status != PROTOMATTER_OK) {
    for(;;);
  }
}

void loop(void) {

  trig = digitalRead(trig_pin);

  Serial.print("Trig state is: ");
  Serial.println(trig);

  if (trig == 0) {
    Serial.println("Waiting for trigger");
  }

  if (trig == 1) {
    matrix.fillRect(0,0,32,32, WHITE);

    matrix.fillCircle(15, 15, 1, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 2, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 3, BLACK);
    matrix.show();
    delay(delayTime);

    matrix.fillCircle(15, 15, 4, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 5, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 6, BLACK);
    matrix.show();
    delay(delayTime);

    matrix.fillCircle(15, 15, 7, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 8, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 9, BLACK);
    matrix.show();
    delay(delayTime);

    matrix.fillCircle(15, 15, 10, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 11, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 12, BLACK);
    matrix.show();
    delay(delayTime);

    matrix.fillCircle(15, 15, 13, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 14, BLACK);
    matrix.show();
    delay(delayTime);
    
    matrix.fillCircle(15, 15, 15, BLACK);
    matrix.show();
    delay(delayTime);

  }

}
