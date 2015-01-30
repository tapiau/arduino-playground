/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example for Getting Started with nRF24L01+ radios. 
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two 
 * different nodes.  Put one of the nodes into 'transmit' mode by connecting 
 * with the serial monitor and sending a 'T'.  The ping node sends the current 
 * time to the pong node, which responds by sending the value back.  The ping 
 * node can then see how long the whole cycle took.
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

char c[16];
char dummy[16];

void setup(void)
{
  Serial.begin(9600);
  for(int i=0;i<16;i++)
  {
    dummy[i]=0;
  }

  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(void)
{
  // If characters arrived over the serial port...
  if (Serial.available()) 
  {
    c[15] = Serial.read();
    radio.write(dummy,sizeof(dummy));
    radio.write(c,sizeof(c));
    Serial.write(c[15]);
  }
}

