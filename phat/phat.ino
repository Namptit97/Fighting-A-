#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*----- Declare all constant pin to be used ----*/

#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1


const uint64_t pipe = 0xE8E8F0F0E1LL; // This is the transmit pipe to communicate the two module


/*-----Object Declaration ----*/

RF24 radio(CE_PIN, CSN_PIN); // Activate  the Radio

/*-----Declaration of Variables -----*/

int joystick[2];  // Two element array holding the Joystick readings

void setup()   
{
  Serial.begin(9600); /* Opening the Serial Communication */
  radio.begin();
  radio.openWritingPipe(pipe);
}//--(end setup )---


void loop()   /* Runs Continuously */
{
 // Serial.print("X = ",joystick[0]);
  joystick[0] = analogRead(JOYSTICK_X); 
  joystick[1] = analogRead(JOYSTICK_Y); 
  radio.write( joystick, sizeof(joystick) );

}
