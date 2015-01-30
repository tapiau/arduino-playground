#include "Arduino.h"
#include <EEPROM.h>

void setup();
void loop();

unsigned long interval = 2000;
unsigned int shot = 250;
unsigned int state = 0;
unsigned long timeNext = 0;
unsigned long time = 0;
unsigned long timeOld = 0;
String input;
String command;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  int address = 0;
  byte b1 = EEPROM.read(address);
  byte b2 = EEPROM.read(address+1);
  byte b3 = EEPROM.read(address+2);
  byte b4 = EEPROM.read(address+3);
  
  interval = ((b1 << 0) & 0xFF) + ((b2 << 8) & 0xFFFF) + ((b3 << 16) & 0xFFFFFF) + ((b4 << 24) & 0xFFFFFFFF);

  address = 4;
  b1 = EEPROM.read(address);
  b2 = EEPROM.read(address+1);
  
  shot = ((b1 << 0) & 0xFF) + ((b2 << 8) & 0xFFFF);
  
  state = 2;
}

void commands()
{
    String ret = "";
    char tmp[50];
    input.toCharArray(tmp,50);
    
    command = String(strtok(tmp," \n"));
  
    if(command.equals("start"))
    {
        timeNext = 0;
        state = 2;
        ret = command;
    }
    if(command.equals("stop"))
    {
        timeNext = 0;
        state = 1;
        ret = command;
    }
    if(command.equals("time"))
    {
       unsigned int tmp = atoi(strtok(NULL," \n"));
       if(tmp>shot)
       {
         interval = tmp;
         ret = String(interval);
         timeNext = 0;
       }
       else
       {
         command = "interval time needs to be longer than shot time = "+String(shot);
       }
    }
    if(command.equals("shot"))
    {
       unsigned int tmp = atoi(strtok(NULL," \n"));
       if(tmp<interval)
       {
         shot = tmp;
         ret = String(shot);
         timeNext = 0;
       }
       else
       {
         command = "shot time needs to be shorter than interval time = "+String(interval);
       }

    }
    if(command.equals("params"))
    {
        ret = command;
        
        Serial.println(String("time = ")+String(interval));
        Serial.println(String("shot = ")+String(shot));
    }
    if(command.equals("store"))
    {
      ret = command;

      byte b1 = (interval & 0xFF);
      byte b2 = ((interval >> 8) & 0xFF);
      byte b3 = ((interval >> 16) & 0xFF);
      byte b4 = ((interval >> 24) & 0xFF);
      
      int address = 0;
      EEPROM.write(address, b1);
      EEPROM.write(address + 1, b2);
      EEPROM.write(address + 2, b3);
      EEPROM.write(address + 3, b4);

      b1 = (shot & 0xFF);
      b2 = ((shot >> 8) & 0xFF);
      
      address = 4;
      EEPROM.write(address, b1);
      EEPROM.write(address + 1, b2);
    }
    
    if(ret=="")
    {
        Serial.println("ERROR "+command);
    }
}

// the loop function runs over and over again forever
void loop()
{
  time = millis();
  
  if(time>timeOld)
  {
    timeOld = time;
  }
//  if(time<timeOld)
//  {
//    timeNext -= timeOld;
//    timeOld = time;
//  }
  
  if(timeNext<millis())
  {
    switch(state)
    {
      case 0:
          // idle
        break;
      case 1:
        Serial.println("Stop");
        Serial.println("LO");
        digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
        state = 0;
        timeNext = 0; 
        break;
      case 2:
        Serial.println("Start");
        state = 4;
        timeNext = millis()+interval;        
        break;
      case 3:
        Serial.println("HI");
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
        state = 4;
        timeNext += shot;        
        break;
      case 4:
        Serial.println("LO");
        digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
        state = 3;
        timeNext += interval;
        break;
    }
  }

  if (Serial.available() > 0)
  {
      input = Serial.readString();
      Serial.println(input);
      commands();
  }
}

