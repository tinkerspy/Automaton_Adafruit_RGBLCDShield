#ifndef Automaton_Adafruit_RGBLCDShield_Display_h
#define Automaton_Adafruit_RGBLCDShield_Display_h

#include <Automaton.h>
#include <Adafruit_RGBLCDShield.h>

#undef ATM_CLASSNAME
#define ATM_CLASSNAME Automaton_Adafruit_RGBLCDShield_Display

#define read_menu(addr) (char)pgm_read_byte_near(addr)

typedef char display_t[2][16];

class ATM_CLASSNAME : public Machine {

  public:
  ATM_CLASSNAME( void ) : Machine() { class_label = "LCDIS"; };
  
  // Event and signal names ( EVT_XXX == SIG_XXX allows for a very simple one line event() handler! )
  // Also matches the Adafruit button bitmap, so that BUTTON_XXX lines up with EVT_XXX as follows:
  //   BUTTON_XXX equals (1 << EVT_XXX) equals (1 << SIG_XXX)
  
  enum { EVT_SELECT, EVT_RIGHT, EVT_DOWN, EVT_UP, EVT_LEFT, ELSE } EVENTS;
  enum { SIG_SELECT, SIG_RIGHT, SIG_DOWN, SIG_UP, SIG_LEFT } SIGNALS;

  Adafruit_RGBLCDShield lcd;
  const char *menu_opts;
  int start_action, end_action, top_offset, top_cnt;
  display_t ist, soll = { // German for 'what is' (ist) and 'what should be' (soll)
	{ ' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
    { ' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' } };
 
  ATM_CLASSNAME & menu( const char def[], int act_start, int act_end, int top_offset, int top_cnt );
  int event( int id );
  void action( int id );
  void printXY( int x, int y, const char s[] );
  int updateDisplay( int max_updates );
  int updateDisplay( void );
  virtual void menu_action( int id );
};

#endif
