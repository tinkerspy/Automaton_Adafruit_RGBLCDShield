#pragma once

#include <Automaton.h>
#include <Adafruit_RGBLCDShield.h>

#define read_menu(addr) (char)pgm_read_byte_near(addr)

typedef char display_t[2][16];

class Automaton_Adafruit_RGBLCDShield_Display : public Machine {

  public:
  Automaton_Adafruit_RGBLCDShield_Display( void ) : Machine() {};
  
  // Event and message names ( EVT_XXX == MSG_XXX allows for a very simple one line event() handler! )
  // Also matches the Adafruit button bitmap, so that BUTTON_XXX lines up with EVT_XXX as follows:
  //   BUTTON_XXX equals (1 << EVT_XXX) equals (1 << MSG_XXX)
  
  enum { EVT_SELECT, EVT_RIGHT, EVT_DOWN, EVT_UP, EVT_LEFT, ELSE } EVENTS;
  enum { MSG_SELECT, MSG_RIGHT, MSG_DOWN, MSG_UP, MSG_LEFT, MSG_END } MESSAGES;
  
  Adafruit_RGBLCDShield lcd;
  const char *menu_opts;
  int start_action, end_action, top_offset, top_cnt;
  display_t ist, soll = { // German for 'what is' (ist) and 'what should be' (soll)
	{ ' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
    { ' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' } };
 
  Automaton_Adafruit_RGBLCDShield_Display & menu( const char def[], int act_start, int act_end, int top_offset, int top_cnt );
  int event( int id );
  void action( int id );
  void printXY( int x, int y, const char s[] );
  int updateDisplay( int max_updates );
  int updateDisplay( void );
  virtual void menu_action( int id ) = 0; // Pure virtual method -> makes this an abstract class
  Machine & msgMap( uint32_t map );
};


