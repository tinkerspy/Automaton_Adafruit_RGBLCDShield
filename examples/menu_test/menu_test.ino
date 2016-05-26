#include <Automaton.h>
#include <Automaton_Adafruit_RGBLCDShield_Buttons.h>
#include "Atm_Menu.h"

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>

Atm_led led1, led2, led3; 
Atm_Menu lcd_display;
Automaton_Adafruit_RGBLCDShield_Buttons lcd_buttons;
Appliance app; 

int pin1 = 4;
int pin2 = 5;
int pin3 = 6;

void setup() {
  
  app.component( 
    led1.begin( pin1 )
      .blink( 500 )
      .trigger( led1.EVT_BLINK ) 
  );
  app.component( 
    led2.begin( pin2 )
      .blink( 500 )
      .trigger( led2.EVT_BLINK )
  );
  app.component( 
    led3.begin( pin3 )
      .blink( 500 )
      .trigger( led3.EVT_BLINK )
  );
  app.component( lcd_display.begin( ) );
  app.component( lcd_buttons.begin( lcd_display ) ); // Link the buttons to the display

}

void loop() {
  app.run();
}

