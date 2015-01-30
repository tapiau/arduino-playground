#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);

}

void loop() {
  // put your main code here, to run repeatedly:

}
