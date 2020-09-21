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

// Movement functions

void Move::stop()
{
    analogWrite(RIGHT_FRONT_MOTOR_CR, NO_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_CR, NO_SPEED);
    analogWrite(RIGHT_FRONT_MOTOR_ACR, NO_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_ACR, NO_SPEED);
    analogWrite(LEFT_FRONT_MOTOR_CR, NO_SPEED);
    analogWrite(LEFT_BACK_MOTOR_CR, NO_SPEED);
    analogWrite(RIGHT_FRONT_MOTOR_ACR, NO_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_ACR, NO_SPEED);

    delay(MOVE_STOP_SAFE_DELAY_MS);
}

void Move::forward()
{
    stop();

    analogWrite(RIGHT_FRONT_MOTOR_CR, HIGH_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_CR, HIGH_SPEED);
    analogWrite(LEFT_FRONT_MOTOR_CR, HIGH_SPEED);
    analogWrite(LEFT_BACK_MOTOR_CR, HIGH_SPEED);
}

void Move::backward()
{
    stop();

    analogWrite(RIGHT_FRONT_MOTOR_ACR, HIGH_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_ACR, HIGH_SPEED);
    analogWrite(RIGHT_FRONT_MOTOR_ACR, HIGH_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_ACR, HIGH_SPEED);
}

void Move::right()
{
    stop();

    analogWrite(RIGHT_FRONT_MOTOR_ACR, HIGH_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_ACR, HIGH_SPEED);
    analogWrite(LEFT_FRONT_MOTOR_CR, HIGH_SPEED);
    analogWrite(LEFT_BACK_MOTOR_CR, HIGH_SPEED);
}

void Move::left()
{
    stop();

    analogWrite(RIGHT_FRONT_MOTOR_CR, HIGH_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_CR, HIGH_SPEED);
    analogWrite(RIGHT_FRONT_MOTOR_ACR, HIGH_SPEED);
    analogWrite(RIGHT_BACK_MOTOR_ACR, HIGH_SPEED);
}

void Move::short_test()
{
    forward();
    delay(500);
    backward();
    delay(500);
    right();
    delay(500);
    left();
    delay(500);
    stop();
}

// MMA8451 functions

void MMA8451::init()
{
    MTTEH().check_serial();

    sensor = Adafruit_MMA8451();
    Serial.println("MMA8451 Initialization !");

    if (!sensor.begin()) {
        Serial.println("MMA8451 Initialisation Failed !");
        Serial.println("Program died !");
        program_died();
    }
    Serial.println("MMA8451 Connected!");
    sensor.setRange(MMA8451_RANGE_2_G);
    Serial.print("Range = ");
    Serial.print(2 << sensor.getRange());
    Serial.println("G");
}

void MMA8451::show_X()
{
    Serial.print("X: ");
    Serial.println(sensor.x);
}

void MMA8451::show_Y()
{
    Serial.print("Y: ");
    Serial.println(sensor.y);
}

void MMA8451::show_Z()
{
    Serial.print("Z: ");
    Serial.println(sensor.z);
}

bool MMA8451::Event::get_event()
{
    return sensor.getEvent(&latest);
}

void MMA8451::Event::show_X()
{
    Serial.print("X: ");
    Serial.print(latest.acceleration.x);
    Serial.println("m/s^2");
}

void MMA8451::Event::show_Y()
{
    Serial.print("Y: ");
    Serial.print(latest.acceleration.y);
    Serial.println("m/s^2");
}

void MMA8451::Event::show_Z()
{
    Serial.print("Z: ");
    Serial.print(latest.acceleration.z);
    Serial.println("m/s^2");
}

uint8_t MMA8451::get_orientation()
{
    return sensor.getOrientation();
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