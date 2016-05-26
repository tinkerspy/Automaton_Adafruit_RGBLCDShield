#pragma once

#include <Automaton.h>
#include "pinChange.h"
#include <Adafruit_RGBLCDShield.h>
#include <Automaton_Adafruit_RGBLCDShield_Display.h>

class Atm_Menu : public Automaton_Adafruit_RGBLCDShield_Display {

  public:
  Atm_Menu( void ) : Automaton_Adafruit_RGBLCDShield_Display() {};
  
  // Machine states
  enum { OPT00, OPT10, OPT11, OPT20, OPT21, OPT22, OPT23, OPT30, OPT31, 
			OPT32, OPT33, OPT40, OPT41, OPT42, OPT43, OPT211, OPT311, OPT411 } STATES; 			
  // Menu actions
  enum { ACT00, ACT10, ACT11, ACT20, ACT21, ACT22, ACT23, ACT30, ACT31, 
			ACT32, ACT33, ACT40, ACT41, ACT42, ACT43, ACT11L, ACT211, ACT311, ACT411, UPD } ACTIONS; 
  atm_pin pin;
  
  Atm_Menu & begin( void );
  virtual void menu_action( int id );
};


