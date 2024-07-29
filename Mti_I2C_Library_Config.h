#pragma once

#include <Arduino.h>
#include "Mti_I2C_Library_Custom_Data_Type.h"

#define ENABLE_DEBUG_MODE_MTI_I2C

#define RX_ESP 10
#define TX_ESP 9

#define SLAVE_ADDRESS 0x6C

#define START_CALIB_MODE_BYTE 0x01
#define STOP_CALIB_MODE_BYTE 0x02
#define REQUEST_MTI_DATA_BYTE 0x03
#define SET_FILTER_PROFILE_GENERAL_BYTE 0x04
#define SET_FILTER_PROFILE_HIGH_MAG_BYTE 0x05
#define ENABLE_IN_RUN_COMPASS_CALIB_BYTE 0x06
#define DISABLE_IN_RUN_COMPASS_CALIB_BYTE 0x07

#define DEFAULT_VALUE -999.9

struct i2c_message
{
    bool data_valid = false;

    uint64_t time_since_boot_in_microseconds;

    float x_angle = DEFAULT_VALUE;
    float y_angle = DEFAULT_VALUE;
    float z_angle = DEFAULT_VALUE;

    float acc_x = DEFAULT_VALUE;
    float acc_y = DEFAULT_VALUE;
    float acc_z = DEFAULT_VALUE;

    float turn_rate_x = DEFAULT_VALUE;
    float turn_rate_y = DEFAULT_VALUE;
    float turn_rate_z = DEFAULT_VALUE;

    float cal_value = DEFAULT_VALUE;
};