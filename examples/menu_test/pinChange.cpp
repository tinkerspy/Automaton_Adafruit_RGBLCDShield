#include "pinChange.h"

uint8_t atm_pin::change( uint8_t pin ) {

  unsigned char v = digitalRead( pin ) ? 1 : 0;
  if ( (( pinstate >> pin ) & 1 ) != ( v == 1 ) ) {
    pinstate ^= ( (uint32_t)1 << pin );
    return 1;
  }
  return 0;
}

