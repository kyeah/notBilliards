#include <iostream>

#ifndef __BALL_H__
#define __BALL_H__

#include "./common.h"
#include "./geom2.h"

using namespace std;

struct Color {
  Color() {}
  Color(GLfloat _r, GLfloat _g, GLfloat _b) {
    c[0] = _r;
    c[1] = _g;
    c[2] = _b;
  }
  operator GLfloat*() { return c; }
  GLfloat c[3];
};



// A handy Ball class
class Ball {
 public:
 Ball(GLint _x, GLint _y, GLint _r, Color _c); 
  
  operator GLint*() { return x; }
  GLint operator[](int i) const { return x[i]; }
  GLint x[2];
  GLfloat velocity;
  GLint radius;
  Color c;
  
  void draw();
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
