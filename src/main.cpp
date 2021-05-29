#include <Arduino.h>

// pin definitions
// should be H1-H7 in latin alphabet
#define X1 2
#define X2 3
#define X3 4
#define X4 5
#define X5 6
#define X6 7
#define X7 8

// cathode clock 1
#define CCLK 9

// anode shift register data in pins
#define AD1357 10
#define AD246 11

// both anode shift register clocks connected to one pin
#define ACLK 12

void setCathode(int8_t cathode) {
  // begin clock pulse
  digitalWrite(CCLK,HIGH);
  // MSB X7,X6,X5,X4 LSB counts from 0 to 15
  digitalWrite(X4,cathode & 0x1);
  digitalWrite(X5,((cathode & 0x2)>>1));
  digitalWrite(X6,((cathode & 0x4)>>2));
  digitalWrite(X7,((cathode & 0x8)>>3));
  // MSB X3,X2,X1 LSB counts 0,1,2,3,4
  digitalWrite(X1,((cathode & 0x10)>>4));
  digitalWrite(X2,((cathode & 0x20)>>5));
  digitalWrite(X3,((cathode & 0x40)>>6));
  digitalWrite(CCLK,LOW);
}

void setup() {
  // LED ON until we're done with setup
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);

  // Setting up serial
  Serial.begin(9600);
  Serial.println("MS6205 logic replacement board");

  // Setting up pins  
  pinMode(X1,OUTPUT);
  pinMode(X2,OUTPUT);
  pinMode(X3,OUTPUT);
  pinMode(X4,OUTPUT);
  pinMode(X5,OUTPUT);
  pinMode(X6,OUTPUT);
  pinMode(X7,OUTPUT);
  pinMode(CCLK,OUTPUT);
  pinMode(AD1357,OUTPUT);
  pinMode(AD246,OUTPUT);
  pinMode(ACLK,OUTPUT);

//shift in zebra (10101...)
  digitalWrite(AD1357,HIGH);
  digitalWrite(AD246,LOW);
  for (int i=0;i<40;i++) {
      digitalWrite(ACLK,LOW);
      delayMicroseconds(2);
      digitalWrite(ACLK,HIGH);
      delayMicroseconds(2);
  }
  digitalWrite(ACLK,LOW);

  //setup done
  Serial.println("Setup done");
  digitalWrite(LED_BUILTIN,LOW);
}

void loop() {
  for(uint8_t i=0;i<16;i++) {
    for(uint8_t j=0;j<5;j++) {
      //alternate the Arduino LED on every character
      digitalWrite(LED_BUILTIN,(i & 0x1));
      setCathode((j<<4)|i);
      delay(100);
    }
  }
}
