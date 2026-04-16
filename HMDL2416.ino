/* HMDL2416 --- test HP LED display                                   2024-03-18 */

#include <avr/io.h>

#define WR_PIN 7    // AVR PORTD bit 7
#define A0_PIN 8
#define A1_PIN 9
#define CS_PIN 10

#define HMDL_D0 11  // Avoid using Arduino pins 0 and 1
#define HMDL_D1 12  // because they're the UART
#define HMDL_D2 2   // AVR PORTD bit 2
#define HMDL_D3 4
#define HMDL_D4 4
#define HMDL_D5 5
#define HMDL_D6 6   // AVR PORTD bit 6


void setup(void)
{
  int i;

  Serial.begin(9600);
  Serial.println("\nHMDL2416");
  
  pinMode(WR_PIN, OUTPUT);
  pinMode(A0_PIN, OUTPUT);
  pinMode(A1_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);

  pinMode(HMDL_D0, OUTPUT);
  pinMode(HMDL_D1, OUTPUT);
  
  for (i = HMDL_D2; i <= HMDL_D6; i++)
    pinMode(i, OUTPUT);
  
  digitalWrite(WR_PIN, HIGH);
  digitalWrite(CS_PIN, HIGH);
  digitalWrite(A0_PIN, LOW);
  digitalWrite(A1_PIN, LOW);
  
  digitalWrite(HMDL_D0, LOW);
  digitalWrite(HMDL_D1, LOW);
  
  for (i = HMDL_D2; i <= HMDL_D6; i++)
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

    Serial.write(ch);
    
    delay(300);
  }

  Serial.println("");
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
  
  if (ch & 0x01)
    digitalWrite(HMDL_D0, HIGH);
  else
    digitalWrite(HMDL_D0, LOW);

  if (ch & 0x02)
    digitalWrite(HMDL_D1, HIGH);
  else
    digitalWrite(HMDL_D1, LOW);
  
  digitalWrite(CS_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(WR_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(WR_PIN, HIGH);
  delayMicroseconds(2);
  digitalWrite(CS_PIN, HIGH);
}
