/*
** MTTEH Main Library
** https://github.com/MTTEH/MTTEH_Library
**
** Authors :
**  - Narutarded (https://github.com/narutarder).
**  - Kiradae (https://github.com/Kiradae).
**  - GGLinnk (https://github.com/GGLinnk) <gglinnk@protonmail.com>.
**  - Wabia (https://github.com/wabia).
**
** Licence GPLv3
**
** Lycée Frédéric Ozanam | Cesson-Sévigné | 2018-2019
** Personal Project      | World          | 2018-2020
**
**/

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Adafruit_MMA8451.h>
#include <Wire.h>

#ifndef MTTEH_H_
    #define MTTEH_H_

    #define program_died() while (1)
    #define wait_for(x)    while (!x)

// General functions

void check_serial()

    // MMA8451 functions

    void init_MMA8451();
void read_MMA8451();
void print_X_MMA8451();
void print_Y_MMA8451();
void print_Z_MMA8451();
void print_all_MMA8451();
void get_event_MMA8451();
void print_X_event_MMA8451();
void print_Y_event_MMA8451();
void print_Z_event_MMA8451();
void print_all_event_MMA8451();
uint8_t get_orientation_MMA8451();

// SGP30 functions

void init_SGP30();
bool check_SGP30();
uint16_t get_TVOC_SGP30();
uint16_t get_eCO2_SGP30();
boolean getIAQBaseline_SGP30(uint16_t *eCO2_base, uint16_t *TVOC_base);

// MCP9808 functions

void init_MCP9808();
void wake_MCP9808();
void get_resolution_MCP9808();
float get_temperature_C_MCP9808();
float get_temperature_F_MCP9808();
void stop_MCP9808();

#endif    // MTTEH_H_