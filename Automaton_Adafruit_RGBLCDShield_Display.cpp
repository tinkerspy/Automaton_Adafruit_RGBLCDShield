#include <Automaton.h>
#include "Automaton_Adafruit_RGBLCDShield_Display.h"

Automaton_Adafruit_RGBLCDShield_Display & Automaton_Adafruit_RGBLCDShield_Display::menu( const char def[], int act_start, int act_end, int offset, int cnt )
{ 
  menu_opts = def;
  lcd = Adafruit_RGBLCDShield();
  lcd.begin( 16, 2 );
  start_action = act_start;
  end_action = act_end;
  top_offset = offset;
  top_cnt = cnt;
  Machine::begin( state_table, ELSE, messages, MSG_END );
 // msg_queue = messages;
 // msg_max = MSG_END;
  return *this;
}

int Automaton_Adafruit_RGBLCDShield_Display::event( int id ) 
{
  return id < 5 ? msgRead( id ) : 0; // Only possible because EVT_XXX == SIG_XXX (see .h)
}

// Double buffering: write 'max' changes from the 'soll' buffer to both the lcd and the 'ist' buffer
int Automaton_Adafruit_RGBLCDShield_Display::updateDisplay( int max_updates ) 
{
	uint8_t updates = 0;
	for ( uint8_t y = 0; y < 2; y++ ) {
		for ( uint8_t x = 0; x < 16; x++ ) {
			if ( ist[y][x] != soll[y][x] ) {
				lcd.setCursor( x, y );
				lcd.print( soll[y][x] );
				ist[y][x] = soll[y][x];
				if ( ++updates >= max_updates ) return updates;
			}
		}
	}
	return updates;
}

int Automaton_Adafruit_RGBLCDShield_Display::updateDisplay( void ) 
{
	return updateDisplay( 32 );
}

void Automaton_Adafruit_RGBLCDShield_Display::printXY( int x, int y, const char s[] ) 
{	
	for ( uint8_t i = 0; i < strlen( s ); i++ ) {
		soll[y][x++] = s[i];
	}
}

void Automaton_Adafruit_RGBLCDShield_Display::action( int id ) 
{	
  if ( id >= start_action && id <= end_action ) {
	int parent = read_state( state_table + ( current * width ) + ATM_ON_EXIT + EVT_LEFT + 1 );
	if ( parent >= 0 ) {
	  for ( int x = top_offset; x < top_offset + top_cnt; x++ ) {
		soll[0][x - top_offset] = read_menu( menu_opts + (parent * 16 ) + x );
	  }
	  for ( int x = 0; x < 16; x++ ) {
		soll[1][x] = read_menu( menu_opts + ( ( id - start_action ) * 16 ) + x );
	  }
	}
  }
  if ( id == ATM_ON_SWITCH ) msgClear(); 
  menu_action( id );  
  return;
}

