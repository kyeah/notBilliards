#ifndef __BALL_H__
#define __BALL_H__

#include <iostream>
#include "./common.h"
#include "./geom2.h"

using namespace std;

// A handy Ball class
class Ball {
 public:
  Ball(GLfloat _x, GLfloat _y, GLint _r, Color _c);

  operator GLfloat*() { return x; }
  GLint operator[](int i) const { return x[i]; }
  Color c;
  GLfloat x[2];  // Position
  GLfloat v[2];  // Velocity
  GLfloat a[2];  // Acceleration
  GLfloat mass;
  GLint radius;

  void draw();
  void checkBounds();
  void update(float elapsed_time);
};

const Color kRed = Color(1, 0, 0);
const Color kGreen = Color(0, 1, 0);
const Color kBlue = Color(0, 0, 1);
const Color kYellow = Color(1, 1, 0);
const Color kCyan = Color(0, 1, 1);
const Color kMagenta = Color(1, 0, 1);
const Color kBlack = Color(0, 0, 0);
const Color kWhite = Color(1, 1, 1);

#endif
