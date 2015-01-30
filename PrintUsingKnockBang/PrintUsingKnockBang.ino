#include <TinyTuner2.h>
#include <util/delay.h>

static void OutputOSCCALAssignment( void )
{
  TinyTuner2.tune();

    Serial.print( OSCCAL, HEX );

//  delay( 2500 );
  _delay_ms( 2500 );
}

void setup( void )
{
  Serial.begin( 9600 );
  Serial.println( OSCCAL, HEX );
  OutputOSCCALAssignment();
}

void loop( void )
{
  OutputOSCCALAssignment();
}

