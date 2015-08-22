#include <Automaton.h>
#include "Automaton_Adafruit_RGBLCDShield_Display.h"

ATM_CLASSNAME & ATM_CLASSNAME::menu( const char def[], int act_start, int act_end, int offset, int cnt )
{ 
  menu_opts = def;
  lcd = Adafruit_RGBLCDShield();
  lcd.begin( 16, 2 );
  start_action = act_start;
  end_action = act_end;
  top_offset = offset;
  top_cnt = cnt;
  return *this;
}

void ATM_CLASSNAME::menu_action( int id ) { };

int ATM_CLASSNAME::event( int id ) 
{
  return signalRead( id ); // Only possible because EVT_XXX == SIG_XXX (see .h)
}

// Double buffering: write cnt changes from the 'soll' buffer to the display and the 'ist' buffer
int ATM_CLASSNAME::updateDisplay( int max ) 
{
	uint8_t i = 0;
	for ( uint8_t y = 0; y < 2; y++ ) {
		for ( uint8_t x = 0; x < 16; x++ ) {
			if ( ist[y][x] != soll[y][x] ) {
				lcd.setCursor( x, y );
				lcd.print( soll[y][x] );
				ist[y][x] = soll[y][x];
				if ( ++i >= max ) return i;
			}
		}
	}
	return i;
}

void ATM_CLASSNAME::printXY( int x, int y, const char s[] ) 
{	
	for ( int i = 0; i < strlen( s ); i++ ) {
		soll[y][x++] = s[i];
	}
}

void ATM_CLASSNAME::action( int id ) 
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
  if ( id == ATM_ON_SWITCH ) signalClear(); 
  menu_action( id );  
  return;
}

