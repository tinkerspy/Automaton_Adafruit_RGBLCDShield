#ifndef Automaton_Adafruit_RGBLCDShield_Buttons_h
#define Automaton_Adafruit_RGBLCDShield_Buttons_h

#include <Automaton.h>
#include <Adafruit_RGBLCDShield.h>

#undef ATM_CLASSNAME
#define ATM_CLASSNAME Automaton_Adafruit_RGBLCDShield_Buttons

typedef void (*presscb_t)( int press );

class ATM_CLASSNAME : public Machine {

  public:
  // Constructor, leave this unchanged
  ATM_CLASSNAME( void ) : Machine() { class_label = "LCBTN"; };
  
  // Your state, event & action names, customize this 
  enum { IDLE, PRESS, REPEAT } STATES; // In state table row order
  enum { EVT_BTN, EVT_RLS, EVT_DELAY, EVT_REPEAT, ELSE } EVENTS;
  enum { ACT_CHECK, ACT_PRESS } ACTIONS; // Custom event & io constants

  Adafruit_RGBLCDShield lcd;
  uint8_t lcd_buttons;
  void (*callback)( int press ) = 0;
  atm_milli_timer timer_delay, timer_repeat;
  
  // Prototypes for your methods, minimum: begin() & io()
  ATM_CLASSNAME & begin(  presscb_t event_callback );
  int event( int id );
  void action( int id );
};
	
#endif
