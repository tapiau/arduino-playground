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
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop() {
if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done)
    {
      // Fetch the data payload
      done = radio.read( c, sizeof(c) );
      Serial.print("C = ");
      Serial.print(c[0]);
    }
  }
}
