#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

char c[1];

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Sender Starting");
  radio.begin();
  radio.openWritingPipe(pipe);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    c[0] = Serial.read();
    radio.write(c,sizeof(1));
    Serial.write(c[0]);
  }
}
