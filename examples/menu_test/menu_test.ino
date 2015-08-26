#include <Automaton.h>
#include <Atm_led.h>
#include <Automaton_Adafruit_RGBLCDShield_Buttons.h>
#include "Atm_Menu.h"

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>

Atm_led led1, led2,led3; 
Atm_Menu lcd_display;
Automaton_Adafruit_RGBLCDShield_Buttons lcd_buttons;
Factory factory; 

void buttonHandler( int press ) {
  lcd_display.signalMap( press );
}

void setup() {
  // Initialize the machines
  led1.begin( 3 ).blink( 50 ).state( led1.START );
  led2.begin( 4 ).blink( 50 ).state( led2.START );
  led3.begin( 5 ).blink( 50 ).state( led3.START );
  lcd_display.begin( );
  lcd_buttons.begin( buttonHandler );

  // Add the initialized machines to the factory
  factory.add( led1 ).add( led2 ).add( led3 ).add( lcd_buttons ).add( lcd_display );
}

void loop() {
  factory.cycle();
}

