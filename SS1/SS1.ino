#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()  
{

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Goodnight moon!");
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{
  if (mySerial.available())
    mySerial.write(mySerial.read());
}

