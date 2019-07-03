#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "hwlib.hpp"
#include <math.h>

/*! \brief Simple Library for MPU6050/GY-521
 *
 *
 *  This Library provides methods to read Pitch angle, Roll angle and
 * temperature in celcius. Usage requires Wouter van Ooijen's hwlib library
 * (https://github.com/wovo/hwlib)
 */

class mpu6050 {
private:
  hwlib::i2c_bus bus;
  u_int8_t adress;

  //! Acceses the Register for X-Axis Acceleration High, then accesses the
  //! corresponding Low Register,then shifts these into a 16 bit integer
  /*!

    \return  a 16 bit integer depending on measured values. Used by
    ReadPitchAngle()/ReadRollAngle(); \sa ReadPitchAngle(), ReadRollAngle()
  */

  int16_t readRawAcceleX() {
    uint8_t val_H[1] = {0x3B};
    bus.write(adress).write(val_H, 1);
    bus.read(adress).read(val_H, 1);

    uint8_t val_L[1] = {0x3C};
    bus.write(adress).write(val_L, 1);
    bus.read(adress).read(val_L, 1);

    int16_t ret = 0;
    ret = (val_H[0] << 8) + val_L[0];
    return ret;
  }

  //! Acceses the Register for Y-Axis Acceleration High, then accesses the
  //! corresponding Low Register,then shifts these into a 16 bit integer
  /*!

    \return  a 16 bit integer depending on measured values. Used by
    ReadPitchAngle()/ReadRollAngle(); \sa ReadPitchAngle(), ReadRollAngle()
  */

  int16_t readRawAcceleY() {
    uint8_t val_H[1] = {0x3D};
    bus.write(adress).write(val_H, 1);
    bus.read(adress).read(val_H, 1);

    uint8_t val_L[1] = {0x3E};
    bus.write(adress).write(val_L, 1);
    bus.read(adress).read(val_L, 1);

    int16_t ret = 0;
    ret = (val_H[0] << 8) + val_L[0];
    return ret;
  }

  //! Acceses the Register for Z-Axis Acceleration High, then accesses the
  //! corresponding Low Register,then shifts these into a 16 bit integer
  /*!

    \return  a 16 bit integer depending on measured values. Used by
    ReadPitchAngle()/ReadRollAngle(); \sa ReadPitchAngle(), ReadRollAngle()
  */
  int16_t readRawAcceleZ() {
    uint8_t val_H[1] = {0x3F};
    bus.write(adress).write(val_H, 1);
    bus.read(adress).read(val_H, 1);

    uint8_t val_L[1] = {0x40};
    bus.write(adress).write(val_L, 1);
    bus.read(adress).read(val_L, 1);

    int16_t ret = 0;
    ret = (val_H[0] << 8) + val_L[0];
    return ret;
  }

  //! Acceses the Register for X-Axis Gyroscope High, then accesses the
  //! corresponding Low Register,then shifts these into a 16 bit integer
  /*!

    \return  a 16 bit integer depending on measured values.
    */
  int16_t readRawGyroX() {
    uint8_t val_H[1] = {0x43};
    bus.write(adress).write(val_H, 1);
    bus.read(adress).read(val_H, 1);

    uint8_t val_L[1] = {0x44};
    bus.write(adress).write(val_L, 1);
    bus.read(adress).read(val_L, 1);

    int16_t ret = 0;
    ret = (val_H[0] << 8) + val_L[0];
    return ret;
  }

  //! Acceses the Register for X-Axis Gyroscope High, then accesses the
  //! corresponding Low Register,then shifts these into a 16 bit integer
  /*!

    \return  a 16 bit integer depending on measured values.
    */
  int16_t readRawGyroY() {
    uint8_t val_H[1] = {0x45};
    bus.write(adress).write(val_H, 1);
    bus.read(adress).read(val_H, 1);

    uint8_t val_L[1] = {0x46};
    bus.write(adress).write(val_L, 1);
    bus.read(adress).read(val_L, 1);

    int16_t ret = 0;
    ret = (val_H[0] << 8) + val_L[0];
    return ret;
  }

  //! Acceses the Register for X-Axis Gyroscope High, then accesses the
  //! corresponding Low Register,then shifts these into a 16 bit integer
  /*!

    \return  a 16 bit integer depending on measured values.
    */
  int16_t readRawGyroZ() {
    uint8_t val_H[1] = {0x47};
    bus.write(adress).write(val_H, 1);
    bus.read(adress).read(val_H, 1);

    uint8_t val_L[1] = {0x48};
    bus.write(adress).write(val_L, 1);
    bus.read(adress).read(val_L, 1);

    int16_t ret = 0;
    ret = (val_H[0] << 8) + val_L[0];
    return ret;
  }

public:
  //! Construcs a mpu6050 type object, required parameters are a i2c_bus and the
  //! adress of the MPU6050(depends on AD0 pin level).

  mpu6050(hwlib::i2c_bus &bus, const u_int8_t &adress)
      : bus(bus), adress(adress) {}

  //! Initialize the MPU.
  //! It does this by creating a char array with the following bits:
  //! 0x6B= This selects the 107th register(PowerManagement/Sleep Mode),and
  //! writes 0x00 to it to disable sleep mode.
  //! After waiting 20 Milliseconds, it prints a message to the console to
  //! signify that the transaction has taken place.
  /*!

    \return none(void)
    */

  void init() {
    const uint8_t start[2] = {0x6B, 0x00};
    bus.write(adress).write(start, 2);
    hwlib::wait_ms(20);
    hwlib::cout << "MPU initialized" << hwlib::endl;
  }

  float readTemp() {
    uint8_t val_H[1] = {0x41};
    bus.write(adress).write(val_H, 1);
    bus.read(adress).read(val_H, 1);

    uint8_t val_L[1] = {0x42};
    bus.write(adress).write(val_L, 1);
    bus.read(adress).read(val_L, 1);

    int16_t ret = 0;
    ret = (val_H[0] << 8) + val_L[0];
    float celcius = (ret / 340) + 32.5;
    return celcius;
  }

  //! Method to read Roll Angle, values are obtained from calling private
  //! functions containted in the Class. These values are then calculated into a
  //! integer in Arc-Degrees.
  /*!

    \return Returns the Roll angle in Arc-Degrees.
    */

  int16_t readRollAngle() {

    int_fast16_t xa = readRawAcceleX();
    int_fast16_t ya = readRawAcceleY();
    int_fast16_t za = readRawAcceleZ();
    int_fast16_t rollAngle =
        (atan(ya / sqrt((xa * xa) + (za * za))) * 180 / 3.14156) - 0.59;
    return rollAngle;
  }

  //! Method to read Pitch Angle, values are obtained from calling private
  //! functions containted in the Class. These values are then calculated into a
  //! integer in Arc-Degrees.
  /*!

    \return Returns the Pitch angle in Arc-Degrees.
    */

  int16_t readPitchAngle() {
    int_fast16_t xa = readRawAcceleX();
    int_fast16_t ya = readRawAcceleY();
    int_fast16_t za = readRawAcceleZ();
    int_fast16_t pitchAngle =
        (atan(xa / sqrt((ya * ya) + (za * za))) * 180 / 3.14156) - 0.59;
    return pitchAngle;
  }
};
#endif // MPU6050_HPP