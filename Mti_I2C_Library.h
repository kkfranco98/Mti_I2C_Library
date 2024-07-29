#pragma once

#include "Mti_I2C_Library_Config.h"

#include <Wire.h>

class Mti_I2C_Library
{

private:
    int _i2c_address;

    int _number_of_sample_for_filter;

    i2c_message messaggio_ricevuto;

    angle_axis _offset_angle;

public:
    Mti_I2C_Library(int i2c_address, int number_of_sample_for_filter = 10) : _i2c_address(i2c_address), _number_of_sample_for_filter(number_of_sample_for_filter)
    {
        _offset_angle.x_angle = 0.0;
        _offset_angle.y_angle = 0.0;
        _offset_angle.z_angle = 0.0;
    }

    void begin(FILTER_PROFILE, bool);

    void set_angle_offset(angle_axis offset_angle);

    bool update();

    uint64_t get_sample_time();

    angle_axis get_angle_axis_without_offset();
    acceleration_axis get_acceleration_axis();
    angular_speed_axis get_angular_speed_axis();

    angle_axis get_angle_axis_with_offset();
};