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
**/

#ifndef MTTEH_H_
#define MTTEH_H_

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define NO_SPEED     0
#define LOW_SPEED    10
#define MEDIUM_SPEED 50
#define HIGH_SPEED   100

#define MOVE_STOP_SAFE_DELAY_MS 20    // Delay >= 20ms recommended

#define RIGHT_FRONT_MOTOR_CR  0
#define RIGHT_FRONT_MOTOR_ACR 0
#define LEFT_FRONT_MOTOR_CR   0
#define LEFT_FRONT_MOTOR_ACR  0
#define RIGHT_BACK_MOTOR_CR   0
#define RIGHT_BACK_MOTOR_ACR  0
#define LEFT_BACK_MOTOR_CR    0
#define LEFT_BACK_MOTOR_ACR   0

#include <Adafruit_Sensor.h>

#define program_died() while (1)
#define wait_for(x)    while (!x)

class MTTEH
{
  public:
    void check_serial();
    static MMA8451 mma8451;
    static Move movement;
};

// Movement functions

class Move
{
  public:
    void stop();
    void forward();
    void backward();
    void right();
    void left();
    void short_test();
};

// MMA8451 functions

#include <Adafruit_MMA8451.h>

class MMA8451
{
  public:
    static Adafruit_MMA8451 sensor;
    void init();
    void show_X();
    void show_Y();
    void show_Z();
    class Event
    {
      public:
        static sensors_event_t latest;
        bool get_event();
        void show_X();
        void show_Y();
        void show_Z();
    };
    uint8_t get_orientation();
    Event event = Event();
};

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