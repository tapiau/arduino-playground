char data;

void setup() {
//  OSCCAL = 0x4B;
  Serial.begin(9600);
  Serial.println("Hello world!");
}

void loop() {
  Serial.write('\r');
  Serial.write('\n');
  delay(1000);
  
  Serial.print("UDR=");
  Serial.print(UDR,HEX);
  Serial.write('\r');
  Serial.write('\n');

  Serial.print("UCSRA=");
  Serial.print(UCSRA,HEX);
  Serial.write('\r');
  Serial.write('\n');
  
  Serial.print("UCSRB=");
  Serial.print(UCSRB,HEX);
  Serial.write('\r');
  Serial.write('\n');
  
  Serial.print("UCSRC=");
  Serial.print(UCSRC,HEX);
  Serial.write('\r');
  Serial.write('\n');

  Serial.print("UBRRL=");
  Serial.print(UBRRL,HEX);
  Serial.write('\r');
  Serial.write('\n');

  Serial.print("UBRRH=");
  Serial.print(UBRRH,HEX);
  Serial.write('\r');
  Serial.write('\n');
  
  if (Serial.available()>0)
  {
    data = UDR;
    delay(100);
    
    Serial.print("Data=");
    Serial.write(data);
  }
}

