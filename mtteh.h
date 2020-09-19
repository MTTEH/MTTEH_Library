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
#define wait_for(x) while (!x)

#define MAvD1 2
#define MAvD2 3
#define MAvG1 4
#define MAvG2 5
#define MArD1 6
#define MArD2 7
#define MArG1 8
#define MArG2 9

// MMA8451 functions

void check_serial()
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

#endif //MTTEH_H_