#include <Automaton.h>
#include <Automaton_Adafruit_RGBLCDShield_Buttons.h>
#include "Atm_Menu.h"

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>

Atm_led led1, led2, led3, led4; 
Atm_Menu lcd_display;
Automaton_Adafruit_RGBLCDShield_Buttons lcd_buttons;
Appliance app; 

void setup() {
  
  // Initialize the machines
  led1.begin( 3 ).blink( 500 ).trigger( led4.EVT_BLINK );
  led2.begin( 4 ).blink( 500 ).trigger( led4.EVT_BLINK );
  led3.begin( 5 ).blink( 500 ).trigger( led4.EVT_BLINK );
  led4.begin( 6 ).blink( 0 ).pause( 0 ).fade( 0 ).trigger( led4.EVT_BLINK );
  lcd_display.begin( );
  lcd_buttons.begin( lcd_display ); // Link the buttons to the display

  // Add the initialized machines to the factory
  app.component( led4 ).component( led3 ).component( led2 ).component( led1 );
  app.component( lcd_display ).component( lcd_buttons );
}

void loop() {
  app.run();
}

