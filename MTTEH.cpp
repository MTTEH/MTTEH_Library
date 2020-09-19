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
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#include <Adafruit_Sensor.h>
#include <MTTEH.h>
#include <Wire.h>

// Global functions

void check_serial()
{
    if (!Serial)
        program_died();
}

// MMA8451 functions

#include <Adafruit_MMA8451.h>

Adafruit_MMA8451 mma_gyroaccel_sensor = Adafruit_MMA8451();
sensors_event_t mma_gyroaccel_event;

void init_MMA8451()
{
    check_serial();

    Serial.println("MMA8451 Initialization !");

    if (!mma_gyroaccel_sensor.begin()) {
        Serial.println("MMA8451 Initialisation Failed !");
        Serial.println("Program died !");
        program_died();
    }
    Serial.println("MMA8451 Connected!");
    mma_gyroaccel_sensor.setRange(MMA8451_RANGE_2_G);
    Serial.print("Range = ");
    Serial.print(2 << mma_gyroaccel_sensor.getRange());
    Serial.println("G");
}

void read_MMA8451()
{
    mma_gyroaccel_sensor.read();
}

void print_X_MMA8451()
{
    Serial.print("X: ");
    Serial.println(mma_gyroaccel_sensor.x);
}

void print_Y_MMA8451()
{
    Serial.print("Y: ");
    Serial.println(mma_gyroaccel_sensor.y);
}

void print_Z_MMA8451()
{
    Serial.print("Z: ");
    Serial.println(mma_gyroaccel_sensor.z);
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
    mma_gyroaccel_sensor.getEvent(&mma_gyroaccel_event);
}

void print_X_event_MMA8451()
{
    Serial.print("X: ");
    Serial.print(mma_gyroaccel_event.acceleration.x);
    Serial.println("m/s^2");
}

void print_Y_event_MMA8451()
{
    Serial.print("Y: ");
    Serial.print(mma_gyroaccel_event.acceleration.y);
    Serial.println("m/s^2");
}

void print_Z_event_MMA8451()
{
    Serial.print("Z: ");
    Serial.print(mma_gyroaccel_event.acceleration.z);
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
    return mma_gyroaccel_sensor.getOrientation();
}

// SGP30 functions

#include <Adafruit_SGP30.h>

Adafruit_SGP30 sgp_gas_sensor;

void init_SGP30()
{
    check_serial();

    Serial.println("SGP30 Initialization !");

    if (!sgp_gas_sensor.begin()) {
        Serial.println("SGP30 Initialisation Failed !");
        Serial.println("Program died !");
        program_died();
    }
    Serial.println("SGP30 Connected!");
    Serial.print("SGP30 serial #");
    Serial.print(sgp_gas_sensor.serialnumber[0], HEX);
    Serial.print(sgp_gas_sensor.serialnumber[1], HEX);
    Serial.println(sgp_gas_sensor.serialnumber[2], HEX);

    // sgp_gas_sensor.setIAQBaseline(0x8E68, 0x8F41);
}

bool check_SGP30()
{
    if (!sgp_gas_sensor.IAQmeasure()) {
        Serial.println("SGP30 Measurement Failed !");
        return true;
    }
    return false;
}

uint16_t get_TVOC_SGP30()
{
    return sgp_gas_sensor.TVOC;
}

uint16_t get_eCO2_SGP30()
{
    return sgp_gas_sensor.eCO2;
}

boolean getIAQBaseline_SGP30(uint16_t *eCO2_base, uint16_t *TVOC_base)
{
    return sgp_gas_sensor.getIAQBaseline(eCO2_base, TVOC_base);
}

// MCP9808 functions

#include <Adafruit_MCP9808.h>

Adafruit_MCP9808 mcp_temp_sensor = Adafruit_MCP9808();

void init_MCP9808()
{
    check_serial();

    Serial.println("MCP9808 Initialization !");

    if (!mcp_temp_sensor.begin(0x18)) {
        Serial.println("MCP9808 Initialisation Failed !");
        Serial.println("Program died !");
        program_died();
    }
    Serial.println("MCP9808 Connected!");
    mcp_temp_sensor.setResolution(3);
}

void wake_MCP9808()
{
    Serial.println("Waking up MCP9808...");
    mcp_temp_sensor.wake();
}

void get_resolution_MCP9808()
{
    Serial.print("Resolution in mode: ");
    Serial.println(mcp_temp_sensor.getResolution());
}

float get_temperature_C_MCP9808()
{
    return mcp_temp_sensor.readTempC();
}

float get_temperature_F_MCP9808()
{
    return mcp_temp_sensor.readTempF();
}

void stop_MCP9808()
{
    Serial.println("Shutdown MCP9808...");
    mcp_temp_sensor.shutdown_wake(1);
}