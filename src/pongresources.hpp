#ifndef PONGRESOURCES_HPP
#define PONGRESOURCES_HPP

#include "TrueRandom.hpp"
#include "hwlib.hpp"

// funtion that will generate either -2 or 2, this is used to
// determine the inital direction of the ball
int SpeedGen() {
  int rngseed = RandomRange(1, 100);
  int tempspeed = 0;
  if (rngseed > 50) {
    tempspeed = -2;
  } else {
    tempspeed = 2;
  }
  return tempspeed;
}

// Generic object class that includes coordinates, and a draw()function, and a
// print function for debugging

class object {
private:
public:
  hwlib::window &w;
  hwlib::xy start;
  hwlib::xy end;
  object(hwlib::window &w, hwlib::xy start, hwlib::xy end)
      : w(w), start(start), end(end) {}

  void draw() {
    for (int hpixel = start.x; hpixel <= end.x; hpixel++) {
      for (int bpixel = start.y; bpixel <= end.y; bpixel++) {
        w.write(hwlib::xy(hpixel, bpixel));
      }
    }
    // w.flush();
  }

  void print() {
    hwlib::cout << "start x: " << start.x << " end x :" << end.x << hwlib::endl;
    hwlib::cout << "start y: " << start.y << " end y :" << end.y << hwlib::endl;
  }
};

// ball class that generates a 2x2 object with a move function,  and a function
// that allows it to "Bounce" later on.
class ball : public object {

public:
  int speedx;
  int speedy;

  ball(hwlib::window &w, hwlib::xy start, int speedx, int speedy)
      : object(w, start, (start + hwlib::xy(1, 1))), speedx(speedx),
        speedy(speedy) {}

  void move() {
    start = start + hwlib::xy(speedx, speedy);
    end = end + hwlib::xy(speedx, speedy);
    draw();
  }
  void change_speed_factor(int x, int y) {
    speedx *= x;
    speedy *= y;
  }
};

// Ball but with random spawn betweem the middle 25% of the window, both height
// and width wise. Also uses earlier function to generate a random starting
// direction
class RandomBall : public ball {
  int width;
  int height;

public:
  RandomBall(hwlib::window &w, int width, int height)
      : ball(w,
             hwlib::xy(RandomRange(3 * width / 8, 5 * width / 8),
                       RandomRange(3 * height / 8, 5 * height / 8)),
             SpeedGen(), SpeedGen()),
        width(width), height(height) {}
  void reset() { // Resets the object, using different random vales to start with.
    start = hwlib::xy(RandomRange(3 * width / 8, 5 * width / 8),
                      RandomRange(3 * height / 8, 5 * height / 8));
    end = start + hwlib::xy(1, 1);
    speedx = SpeedGen();
    speedy = SpeedGen();
  }
};

// Bat/paddle with move up/down functionality
class bat : public object {
private:
public:
  bat(hwlib::window &w, hwlib::xy start, hwlib::xy end)
      : object(w, start, end) {}

  void movedown() {
    start = start + hwlib::xy(0, 5);
    end = end + hwlib::xy(0, 5);
    draw();
  }
  void moveup() {
    start = start + hwlib::xy(0, -5);
    end = end + hwlib::xy(0, -5);
    draw();
  }
};

#endif // PONGRESOURCES_HPP