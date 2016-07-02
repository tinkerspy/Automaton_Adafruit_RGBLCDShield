#include <Automaton.h>
#include <Automaton_Adafruit_RGBLCDShield_Buttons.h>
#include "Atm_Menu.h"

#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>

Atm_led led1, led2, led3; 
Atm_Menu lcd_display;
Automaton_Adafruit_RGBLCDShield_Buttons lcd_buttons;

int pin1 = 4;
int pin2 = 5;
int pin3 = 6;

void setup() {
  
  led1.begin( pin1 )
    .blink( 500, 500 )
    .start();
  led2.begin( pin2 )
    .blink( 500, 500 )
    .start();
  led3.begin( pin3 )
    .blink( 500, 500 )
    .start();

  lcd_display.begin(;
  lcd_buttons.begin( lcd_display ); // Link the buttons to the display

}

void loop() {
  automaton.run();
}

