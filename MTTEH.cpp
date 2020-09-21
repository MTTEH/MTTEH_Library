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

#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#include "MTTEH.hpp"

// Global functions

void check_serial()
{
    if (!Serial)
        program_died();
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