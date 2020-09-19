#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

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

#endif //MTTEH_H_