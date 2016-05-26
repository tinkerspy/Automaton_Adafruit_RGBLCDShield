#pragma once

#include <Arduino.h>

class atm_pin { 
    uint32_t pinstate;
    public:
        uint8_t change( uint8_t pin );
};
