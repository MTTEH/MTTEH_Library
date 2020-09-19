/*
** MTTEH Library
** Created by GGLinnk <gglinnk@protonmail.com>
*/

#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#include <MTTEH.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

// Global functions

void check_serial()
{
    if (!Serial)
        program_died();
}

// MMA8451 functions

#include <Adafruit_MMA8451.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
sensors_event_t event;

void init_MMA8451()
{
    check_serial();

    Serial.println("MMA8451 Initialization !");

    if (!mma.begin()) {
        Serial.println("MMA8451 Initialisation Failed !");
        Serial.println("Program died !");
        program_died();
    }
    Serial.println("MMA8451 Connected!");
    mma.setRange(MMA8451_RANGE_2_G);
    Serial.print("Range = "); Serial.print(2 << mma.getRange());  
    Serial.println("G");
}

void read_MMA8451()
{
    mma.read();
}

void print_X_MMA8451()
{
    Serial.print("X: ");
    Serial.println(mma.x); 
}

void print_Y_MMA8451()
{
    Serial.print("Y: ");
    Serial.println(mma.y); 
}

void print_Z_MMA8451()
{
    Serial.print("Z: ");
    Serial.println(mma.z); 
}

void print_all_MMA8451()
{
    print_X_MMA8451();
    print_Y_MMA8451();
    print_Z_MMA8451();
    Serial.println("");
}

void get_event_MMA8451()
{
    mma.getEvent(&event);
}

void print_X_event_MMA8451()
{
    Serial.print("X: ");
    Serial.print(event.acceleration.x);
    Serial.println("m/s^2");
}

void print_Y_event_MMA8451()
{
    Serial.print("Y: ");
    Serial.print(event.acceleration.y);
    Serial.println("m/s^2");
}

void print_Z_event_MMA8451()
{
    Serial.print("Z: ");
    Serial.print(event.acceleration.z);
    Serial.println("m/s^2");
}

void print_all_event_MMA8451()
{
    print_X_event_MMA8451();
    print_Y_event_MMA8451();
    print_Z_event_MMA8451();
    Serial.println("");
}

uint8_t get_orientation_MMA8451()
{
    return mma.getOrientation();
}

// SGP30 functions

#include <Adafruit_SGP30.h>

Adafruit_SGP30 sgp;

void init_SGP30()
{
    check_serial();

    Serial.println("SGP30 Initialization !");

    if (!sgp.begin()) {
        Serial.println("SGP30 Initialisation Failed !");
        Serial.println("Program died !");
        program_died();
    }
    Serial.println("SGP30 Connected!");
    Serial.print("SGP30 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);
}

// MCP9808 functions

#include <Adafruit_MCP9808.h>

Adafruit_MCP9808 mcp = Adafruit_MCP9808();

void init_MCP9808()
{
    check_serial();

    Serial.println("MCP9808 Initialization !");

    if (!mcp.begin(0x18)) {
        Serial.println("MCP9808 Initialisation Failed !");
        Serial.println("Program died !");
        program_died();
    }
    Serial.println("MCP9808 Connected!");
    //sgp.setIAQBaseline(0x8E68, 0x8F41);
    tempsensor.setResolution(3);
}