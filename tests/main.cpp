#include "TrueRandom.hpp"
#include "mpu6050.hpp"
int main(int argc, char **argv) {

  namespace target = hwlib::target;

  auto scl1 = target::pin_oc(target::pins::d21);
  auto sda1 = target::pin_oc(target::pins::d20);
  auto iic = hwlib::i2c_bus_bit_banged_scl_sda(scl1, sda1);
  auto chiptest = mpu6050(iic, 0x68); // AD0 LOW
  chiptest.init();

  // mpu geeft 16 bit signed intergers terug voor meet waarde van de
  // accelerometer  dus van - 32767 tot 32767.

  // de formule voor berekenen van pitch/roll is :
  // atan(x / sqrt((y^2) + (z^2))). Het domein van een inverse tan functie is
  // "-pi/2<=domein<=pi/2" (-90 tot 90 graden). de uitvoer van deze functie zou
  // dus altijd tussen -90 en 90 ongeacht hoe je de mpu6050 draait zijn als de
  // mpu/code goed werkt.

  /// Randomness word ook gestest doormiddel van de RandomRange() functie te
  /// getallen tussen 1000 en 1111 te genereren, als deze dus getalen buiten
  /// 1000 en 1666 genereerd voldoet de randomRange functie niet.

  for (;;) {
    int Pitch = chiptest.readPitchAngle();
    int Roll = chiptest.readRollAngle();
    int random = RandomRange(1000, 1111);
    if ((Pitch <= 90 && Pitch >= -90) && (Roll <= 90 && Roll >= -90) &&
        (random <= 1111 && random >= 1000)) {
      hwlib::cout << "Test passed with Pitch Angle: " << Pitch
                  << " and Roll Angle: " << Roll << " and RNG: " << random
                  << hwlib::endl;
    } else {
      hwlib::cout << "!!!Test FALIED with Pitch  Angle: " << Pitch
                  << " and Roll Angle: " << Roll << " and RNG: " << random
                  << hwlib::endl;
      break;
    }
    hwlib::wait_ms(10);
  }
}
