#include <Automaton.h>
#include <Atm_led.h>
#include "Atm_Menu.h"

extern Atm_led led1, led2, led3;

ATM_CLASSNAME & ATM_CLASSNAME::begin( void )
{ 
    const static state_t state_table[] PROGMEM = {
    /*             ON_ENTER     ON_LOOP  ON_EXIT  EVT_SELECT  EVT_RIGHT  EVT_DOWN    EVT_UP   EVT_LEFT    ELSE */
    /* OPT00  */      ACT00,         -1,      -1,         -1,        -1,       -1,       -1,        -1,  OPT10, // Main menu title, jumps straight to OPT10
    /* OPT10  */      ACT10,        UPD,      -1,         -1,     OPT11,    OPT20,    OPT40,     OPT00,     -1, // First menu option
    /* OPT11  */      ACT11,     ACT11L,      -1,         -1,        -1,    OPT11,    OPT11,     OPT10,     -1, 
    /* OPT20  */      ACT20,        UPD,      -1,         -1,     OPT21,    OPT30,    OPT10,     OPT00,     -1, // Submenu 20
    /* OPT21  */      ACT21,        UPD,      -1,     OPT211,    OPT211,    OPT22,    OPT23,     OPT20,     -1, // First submenu option
    /* OPT22  */      ACT22,        UPD,      -1,         -1,        -1,    OPT23,    OPT21,     OPT20,     -1,
    /* OPT23  */      ACT23,        UPD,      -1,         -1,        -1,    OPT21,    OPT22,     OPT20,     -1,
    /* OPT30  */      ACT30,        UPD,      -1,         -1,     OPT31,    OPT40,    OPT20,     OPT00,     -1, // Submenu 30
    /* OPT31  */      ACT31,        UPD,      -1,     OPT311,    OPT311,    OPT32,    OPT33,     OPT30,     -1, // First submenu option
    /* OPT32  */      ACT32,        UPD,      -1,         -1,        -1,    OPT33,    OPT31,     OPT30,     -1,
    /* OPT33  */      ACT33,        UPD,      -1,         -1,        -1,    OPT31,    OPT32,     OPT30,     -1,
    /* OPT40  */      ACT40,        UPD,      -1,         -1,     OPT41,    OPT10,    OPT30,     OPT00,     -1, // Submenu 40
    /* OPT41  */      ACT41,        UPD,      -1,     OPT411,    OPT411,    OPT42,    OPT43,     OPT40,     -1, // First submenu option
    /* OPT42  */      ACT42,        UPD,      -1,         -1,        -1,    OPT43,    OPT41,     OPT40,     -1,
    /* OPT43  */      ACT43,        UPD,      -1,         -1,        -1,    OPT41,    OPT42,     OPT40,     -1, // Last menu option
    /* OPT211 */     ACT211,         -1,      -1,         -1,        -1,       -1,       -1,        -1,  OPT21, // Actions without corresponding menu options
    /* OPT311 */     ACT311,         -1,      -1,         -1,        -1,       -1,       -1,        -1,  OPT31,
    /* OPT411 */     ACT411,         -1,      -1,         -1,        -1,       -1,       -1,        -1,  OPT41,
    };
    Machine::begin( state_table, ELSE );  
    const static char menu_definition[] PROGMEM = 
    /*            1234567890123456 */
    /* ACT00 */  "00 Main menu    "
    /* ACT10 */  "10 Status      >"
    /* ACT11 */  "11 L1? L2? L3?  "
    /* ACT20 */  "20 Led 1       >"
    /* ACT21 */  "21 Led: ?       "
    /* ACT22 */  "22 On(ms):      "
    /* ACT23 */  "23 Off(ms):     "
    /* ACT30 */  "30 Led 2       >"
    /* ACT31 */  "31 Led: ?       "
    /* ACT32 */  "32 On(ms):      "
    /* ACT33 */  "33 Off(ms):     "
    /* ACT40 */  "40 Led 3       >"
    /* ACT41 */  "41 Led: ?       "
    /* ACT42 */  "42 On(ms):      "
    /* ACT43 */  "43 Off(ms):     ";  
    menu( menu_definition, ACT00, ACT43, 3, 12 );  
    return *this;
}

void ATM_CLASSNAME::menu_action( int id ) 
{
    switch ( id ) {
        case UPD :
            if ( updateDisplay( 1 ) == 0 ) sleep = 1;
            return;
        case ACT11L :
            if ( pinChange( 3 ) ) printXY(  5, 1, digitalRead( 3 ) ? "+" : " " );
            if ( pinChange( 4 ) ) printXY(  9, 1, digitalRead( 4 ) ? "+" : " " );
            if ( pinChange( 5 ) ) printXY( 13, 1, digitalRead( 5 ) ? "+" : " " );
            updateDisplay( 1 );
            return;
        case ACT11 : 
            printXY(  5, 1, digitalRead( 3 ) ? "+" : " " );
            printXY(  9, 1, digitalRead( 4 ) ? "+" : " " );
            printXY( 13, 1, digitalRead( 5 ) ? "+" : " " );
            return;
        case ACT21 : printXY( 8, 1, led1.state() == led1.IDLE ? "Off" : "On" ); return;
        case ACT31 : printXY( 8, 1, led2.state() == led2.IDLE ? "Off" : "On" ); return;
        case ACT41 : printXY( 8, 1, led3.state() == led3.IDLE ? "Off" : "On" ); return;
        case ACT211 : led1.toggle( led1.IDLE, led1.START ); return;
        case ACT311 : led2.toggle( led2.IDLE, led2.START ); return;
        case ACT411 : led3.toggle( led3.IDLE, led3.START ); return;    
    }
}
