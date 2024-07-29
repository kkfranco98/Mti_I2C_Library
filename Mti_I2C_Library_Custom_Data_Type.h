#pragma once

#include <Arduino.h>

enum FILTER_PROFILE
{
    HIGH_MAG,
    GENERAL
};

struct float_sample
{
    uint64_t time_since_boot_in_microseconds = 0;
    float value = 0.0;
};

struct angle_axis
{
    float x_angle = 0.0;
    float y_angle = 0.0;
    float z_angle = 0.0;

    // Definizione dell'operatore di somma
    angle_axis operator+(const angle_axis &other) const
    {
        angle_axis result;
        result.x_angle = this->x_angle + other.x_angle;
        result.y_angle = this->y_angle + other.y_angle;
        result.z_angle = this->z_angle + other.z_angle;
        return result;
    }

    // Definizione dell'operatore di sottrazione
    angle_axis operator-(const angle_axis &other) const
    {
        angle_axis result;
        result.x_angle = this->x_angle - other.x_angle;
        result.y_angle = this->y_angle - other.y_angle;
        result.z_angle = this->z_angle - other.z_angle;
        return result;
    }
};

struct acceleration_axis
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
};

struct angular_speed_axis
{
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
};