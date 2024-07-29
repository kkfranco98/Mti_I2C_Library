#include "Mti_I2C_Library.h"

void Mti_I2C_Library::begin(FILTER_PROFILE filter_profile, bool enable_in_run_compass_calibration)
{
        Wire.begin();

        delay(100);

        switch (filter_profile)
        {
        case FILTER_PROFILE::HIGH_MAG:
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("\n============================================\nSetting filter profile to high mag");
#endif
                Wire.beginTransmission(_i2c_address);
                Wire.write(SET_FILTER_PROFILE_HIGH_MAG_BYTE);
                Wire.endTransmission();
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("Done setting filter profile to high mag\n");
#endif
                break;

        case FILTER_PROFILE::GENERAL:
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("\n============================================\nSetting filter profile to general");
#endif
                Wire.beginTransmission(_i2c_address);
                Wire.write(SET_FILTER_PROFILE_GENERAL_BYTE);
                Wire.endTransmission();
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("Done setting filter profile to general\n");
#endif
                break;

        default:
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("\n============================================\nSetting filter profile to default");
#endif
                Wire.beginTransmission(_i2c_address);
                Wire.write(SET_FILTER_PROFILE_GENERAL_BYTE);
                Wire.endTransmission();
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("Done setting filter profile to default\n");
#endif
                break;
        }

        if (enable_in_run_compass_calibration)
        {
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("\n============================================\nEnabling in run compass calibration");
#endif
                Wire.beginTransmission(_i2c_address);
                Wire.write(ENABLE_IN_RUN_COMPASS_CALIB_BYTE);
                Wire.endTransmission();
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("Done enabling in run compass calibration\n");
#endif
        }
        else
        {
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("\n============================================\nDisabling in run compass calibration");
#endif
                Wire.beginTransmission(_i2c_address);
                Wire.write(DISABLE_IN_RUN_COMPASS_CALIB_BYTE);
                Wire.endTransmission();
#ifdef ENABLE_DEBUG_MODE_MTI_I2C
                Serial.println("Done disabling in run compass calibration\n");
#endif
        }
}

bool Mti_I2C_Library::update()
{
        Wire.beginTransmission(_i2c_address);
        Wire.write(REQUEST_MTI_DATA_BYTE);
        Wire.endTransmission();

        // Richiedi la struct allo slave
        Wire.requestFrom(_i2c_address, sizeof(messaggio_ricevuto));
        while (Wire.available())
        {
                Wire.readBytes((byte *)&messaggio_ricevuto, sizeof(messaggio_ricevuto));
        }

        if (messaggio_ricevuto.data_valid)
        {
                return true;
        }
        return false;
}

uint64_t Mti_I2C_Library::get_sample_time()
{
        return messaggio_ricevuto.time_since_boot_in_microseconds;
}

angle_axis Mti_I2C_Library::get_angle_axis_without_offset()
{
        angle_axis result;

        result.x_angle = messaggio_ricevuto.x_angle;
        result.y_angle = messaggio_ricevuto.y_angle;
        result.z_angle = messaggio_ricevuto.z_angle;

        return result;
}

angle_axis Mti_I2C_Library::get_angle_axis_with_offset()
{
        return _offset_angle + get_angle_axis_without_offset();
}

void Mti_I2C_Library::set_angle_offset(angle_axis offset_angle)
{
        _offset_angle = offset_angle;
}

acceleration_axis Mti_I2C_Library::get_acceleration_axis()
{
        acceleration_axis result;

        result.x = messaggio_ricevuto.acc_x;
        result.y = messaggio_ricevuto.acc_y;
        result.z = messaggio_ricevuto.acc_z;

        return result;
}

angular_speed_axis Mti_I2C_Library::get_angular_speed_axis()
{
        angular_speed_axis result;

        result.x = messaggio_ricevuto.turn_rate_x;
        result.y = messaggio_ricevuto.turn_rate_y;
        result.z = messaggio_ricevuto.turn_rate_z;

        return result;
}