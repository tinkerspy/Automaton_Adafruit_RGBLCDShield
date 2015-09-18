#include <Automaton.h>
#include "Automaton_Adafruit_RGBLCDShield_Buttons.h"

Automaton_Adafruit_RGBLCDShield_Buttons & Automaton_Adafruit_RGBLCDShield_Buttons::begin()
{ 
  const static state_t state_table[] PROGMEM = {
  /*            ON_ENTER     ON_LOOP  ON_EXIT  EVT_SAMPLE  EVT_BTN   EVT_RLS  EVT_DELAY  EVT_REPEAT  ELSE */
  /* IDLE   */ ACT_CHECK,         -1,      -1,       IDLE,   PRESS,       -1,        -1,         -1,   -1, 
  /* PRESS  */ ACT_PRESS,  ACT_CHECK,      -1,         -1,      -1,     IDLE,    REPEAT,         -1,   -1, 
  /* REPEAT */ ACT_PRESS,  ACT_CHECK,      -1,         -1,      -1,     IDLE,        -1,     REPEAT,   -1, 
  };
  Machine::begin( state_table, ELSE );
  lcd = Adafruit_RGBLCDShield();
  lcd.begin(16, 2);
  set(  timer_delay, 500 );
  set( timer_repeat, 100 );  
  set( timer_sample,  50 );
  return *this;
}

Automaton_Adafruit_RGBLCDShield_Buttons & Automaton_Adafruit_RGBLCDShield_Buttons::begin( presscb_t event_callback ) 
{
  callback = event_callback;
  this->begin();
  return *this;
}

Automaton_Adafruit_RGBLCDShield_Buttons & Automaton_Adafruit_RGBLCDShield_Buttons::begin( const char label[] )
{
  display = factory->find( label );
  this->begin();
  return *this;
}

Automaton_Adafruit_RGBLCDShield_Buttons & Automaton_Adafruit_RGBLCDShield_Buttons::begin( Machine & machine )
{
  display = &machine;
  this->begin();
  return *this;
}

int Automaton_Adafruit_RGBLCDShield_Buttons::event( int id ) 
{
  switch ( id ) {
	  case EVT_SAMPLE :
		return expired( timer_sample );
	  case EVT_BTN :
		return lcd_buttons > 0;
	  case EVT_RLS :
		return lcd_buttons == 0;
	  case EVT_DELAY :
		return expired( timer_delay );
	  case EVT_REPEAT :
		return expired( timer_repeat );
  }
  return 0;
}

void Automaton_Adafruit_RGBLCDShield_Buttons::action( int id ) 
{
  switch ( id ) {
	  case ACT_CHECK :
		lcd_buttons = lcd.readButtons();
		return;
	  case ACT_PRESS :
        if ( display ) display->msgMap( lcd_buttons );
		if ( callback ) (*callback)( lcd_buttons );
		return;
  }
}


