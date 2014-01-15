/*
 * Read data from any serial ports an relay it to other ports
 */
#define BAUD 4800
#define LED_PIN 13

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200); // USB output
  
  // Hardware Serial
  Serial1.begin(BAUD);
  Serial2.begin(BAUD);
  Serial3.begin(BAUD);  
}

char c=0;
char n=0;
uint16_t m=0;

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  m++;

  while (Serial1.available())
  {
    if (c!=1)
    {
      c=1;
      Serial.print("\r\nSER1 ");
      Serial.print(millis());
    }
      n++;
      m=0;
      Serial.print(" ");
      uint8_t i=Serial1.read();
      if (i<=0xf) Serial.print("0");
      Serial.print(i, HEX);
      Serial2.write(i);
      Serial3.write(i);
  }

  while (Serial2.available())
  {
    if (c!=2)
    {
      c=2;
      Serial.print("\r\nSER2 ");
      Serial.print(millis());
    }
      n++;
      m=0;
      Serial.print(" ");
      uint8_t i=Serial2.read();
      if (i<=0xf) Serial.print("0");
      Serial.print(i, HEX);
      Serial1.write(i);
      Serial3.write(i);
  }

  while (Serial3.available())
  {
    if (c!=3)
    {
      c=3;
      Serial.print("\r\nSER3 ");
      Serial.print(millis());
    }
      n++;
      m=0;
      Serial.print(" ");
      uint8_t i=Serial3.read();
      if (i<=0xf) Serial.print("0");
      Serial.print(i, HEX);
      Serial1.write(i);
      Serial2.write(i);
  }
  
  if ((n>40) || (m>100)) { c=0; n=0; m=0; }
  
  digitalWrite(LED_PIN, LOW);
  asm volatile("wfi\r\n"::); // sleep until next interrupt
}

