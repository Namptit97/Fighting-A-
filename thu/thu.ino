/*----- Import all required Libraries -----*/
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
/*----- Declare all constant pin to be used ----*/
 
#define CE_PIN   9
#define CSN_PIN 10
 
const uint64_t pipe = 0xE8E8F0F0E1LL; // This is the transmit pipe to communicate the two module
 
 
/*-----Object Declaration ----*/
 
RF24 radio(CE_PIN, CSN_PIN); // Activate the Radio
 
/*-----Declaration of Variables -----*/
 
int joystick[2];  //  Two element array holding the Joystick readings
 
#define in1 A2   // A+
#define in2 A3   // A-
#define in3 A4// B-
#define in4 A5  // B+
#define ena A0
#define enb A1



int init_speed=80;
int max_speed = 120;

/*
 * cac ham co ban tien lui , dung , quay trai , phai 
 * su dung de test khi khong dung cac he so PD
*/
void lui(unsigned long ts){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);  
  analogWrite(ena, init_speed); 
  analogWrite(enb, init_speed); 
  delay(ts);
}

void tien(unsigned long ts){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH); 
  analogWrite(ena, init_speed); 
  analogWrite(enb, init_speed);  
  delay(ts);
}

void retrai(unsigned long t){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);  
  analogWrite(ena, init_speed); 
  analogWrite(enb, init_speed); 
  delay(t);
}

void rephai(unsigned long ts){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);  
  analogWrite(ena, init_speed); 
  analogWrite(enb, init_speed); 
  delay(ts);
}
/*
  xac dinh gia tri doc duoc tren cac cam bien 
*/

void setup()
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT);  
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT); 
  digitalWrite(A4, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);  

  Serial.begin(9600); /* Opening the Serial Communication */
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop(){
    if ( radio.available() )
  {
    // Reading the data payload until the RX received everything
    bool done = false;
    while (!done)
    {
      // Fetching the data payload
      done = radio.read( joystick, sizeof(joystick) );
      Serial.print("X = ");
      Serial.print(joystick[0]);
      Serial.print(" Y = ");      
      Serial.println(joystick[1]);
      if ( joystick[0] > 700 && joystick[1] > 300 ) 
      {
        tien(100);
        Serial.print("Tien");
      }
    
      else if ( joystick[0] > 300 && joystick[1] == 0 )
      {
        retrai(100);
        Serial.print("Retrai");
      }

      else if ( joystick[0] == 0 && joystick[1] > 300 )
      {
        lui(100);
        Serial.print("Lui"); 
      }

      else if ( joystick[0] > 300 && joystick[1] > 700 )
      {
        rephai(100);
        Serial.print("Rephai");
      }
    }
  }
  else
  {    
      Serial.println("No radio available");
  }
  }
