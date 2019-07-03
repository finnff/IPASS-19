#include "mpu6050.hpp"
#include "pongresources.hpp"

int main(int argc, char **argv) {

  namespace target = hwlib::target;

  auto scl = target::pin_oc(target::pins::d10);
  auto sda = target::pin_oc(target::pins::d11);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
  auto w = hwlib::glcd_oled(i2c_bus, 0x3c);

  auto scl1 = target::pin_oc(target::pins::d21);
  auto sda1 = target::pin_oc(target::pins::d20);
  auto iic = hwlib::i2c_bus_bit_banged_scl_sda(scl1, sda1);
  auto chipL = mpu6050(iic, 0x68);
  auto chipR = mpu6050(iic, 0x69);

  chipL.init();
  chipR.init();
  int rwidth = 128;
  int rheight = 64;

  int Lscore = 0;
  int Rscore = 0;

  RandomBall b(w, 128, 64);

  bat r(w, hwlib::xy((rwidth - (rwidth / 10)) - 2, rheight / 2),
        hwlib::xy((rwidth - (rwidth / 10)), ((rheight / 2) + (rheight / 5))));

  bat l(w, hwlib::xy(rwidth / 10, rheight / 2),
        hwlib::xy((rwidth / 10 + 2), ((rheight / 2) + (rheight / 5))));

  for (;;) {
    int lroll = chipL.readRollAngle();
    int rroll = chipR.readRollAngle();

    w.clear();
    if (lroll < -30 && l.start.y > 0) {
      l.moveup();
    }
    if (lroll > 30 && l.end.y < rheight) {
      l.movedown();
    }
    if (rroll < -30 && r.start.y > 0) {
      r.moveup();
    }
    if (rroll > 30 && r.end.y < rheight) {
      r.movedown();
    }
    r.draw();
    l.draw();
    b.move();
    if (b.end.x == (rwidth - (rwidth / 10) - 2) ||
        b.end.x == (rwidth - (rwidth / 10) - 3)) { // Right Collision
      if (b.start.y <= r.end.y && b.start.y >= r.start.y) {
        b.change_speed_factor(-1, 1);
      } else {
        Lscore++;
        hwlib::cout << Lscore << " - " << Rscore
                    << hwlib::endl; // Lose condition
        hwlib::wait_ms(500);
        b.reset();
      }
    }
    if (b.start.x == (rwidth / 10) + 1 ||
        b.start.x == (rwidth / 10)) { // Left Collision
      if (b.start.y <= l.end.y && b.start.y >= l.start.y) {
        b.change_speed_factor(-1, 1);

      } else {
        Rscore++;
        hwlib::cout << Lscore << " - " << Rscore
                    << hwlib::endl; // Lose condition
        hwlib::wait_ms(500);
        b.reset();
      }
    }

    if (b.start.y >= rheight - 1 ||
        b.start.y <= 0) { // Bounce top/bottom of screen
      b.change_speed_factor(1, -1);
    }
    w.flush();
  }
}
