/* HMDL2416 --- test HP LED display */

#include <avr/io.h>

#define WR_PIN 7
#define A0_PIN 8
#define A1_PIN 9
#define CS_PIN 10

void setup(void)
{
  int i;
  
  pinMode(WR_PIN, OUTPUT);
  pinMode(A0_PIN, OUTPUT);
  pinMode(A1_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  
  for (i = 0; i < 7; i++)
    pinMode(i, OUTPUT);
  
  digitalWrite(WR_PIN, HIGH);
  digitalWrite(CS_PIN, HIGH);
  digitalWrite(A0_PIN, LOW);
  digitalWrite(A1_PIN, LOW);
  
  for (i = 0; i < 7; i++)
    digitalWrite(i, LOW);
}

void loop(void)
{
  int ch;
  int i;
  
  for (ch = '!'; ch <= '\\'; ch++) {
    for (i = 0; i < 4; i++) {
      HMDL2416Write(3 - i, ch + i);
    }
    
    delay(300);
  }
}

void HMDL2416Write(int digit, int ch)
{
  switch (digit) {
  case 0:
    digitalWrite(A0_PIN, LOW);
    digitalWrite(A1_PIN, LOW);
    break;
  case 1:
    digitalWrite(A0_PIN, HIGH);
    digitalWrite(A1_PIN, LOW);
    break;
  case 2:
    digitalWrite(A0_PIN, LOW);
    digitalWrite(A1_PIN, HIGH);
    break;
  case 3:
    digitalWrite(A0_PIN, HIGH);
    digitalWrite(A1_PIN, HIGH);
    break;
  }
  
  PORTD = ch | 0x80;
  
  digitalWrite(CS_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(WR_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(WR_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(CS_PIN, HIGH);
}
