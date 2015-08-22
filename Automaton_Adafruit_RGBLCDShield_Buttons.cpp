#include <Automaton.h>
#include "Automaton_Adafruit_RGBLCDShield_Buttons.h"

ATM_CLASSNAME & ATM_CLASSNAME::begin( presscb_t event_callback )
{ 
  const static state_t state_table[] PROGMEM = {
  /*            ON_ENTER     ON_LOOP  ON_EXIT  EVT_BTN   EVT_RLS  EVT_DELAY  EVT_REPEAT  ELSE */
  /* IDLE   */        -1,  ACT_CHECK,      -1,   PRESS,       -1,        -1,         -1,   -1, 
  /* PRESS  */ ACT_PRESS,  ACT_CHECK,      -1,      -1,     IDLE,    REPEAT,         -1,   -1, 
  /* REPEAT */ ACT_PRESS,  ACT_CHECK,      -1,      -1,     IDLE,        -1,     REPEAT,   -1, 
  };
  table( state_table, ELSE );
  lcd = Adafruit_RGBLCDShield();
  lcd.begin(16, 2);
  callback = event_callback;
  set( timer_delay, 500 );
  set( timer_repeat,100 );  
  return *this;
}

int ATM_CLASSNAME::event( int id ) 
{
  switch ( id ) {
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

void ATM_CLASSNAME::action( int id ) 
{
  switch ( id ) {
	  case ACT_CHECK :
		lcd_buttons = lcd.readButtons();
		return;
	  case ACT_PRESS :
		(*callback)( lcd_buttons );
		return;
  }
}


