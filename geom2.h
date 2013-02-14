#ifndef __GEOM2_H__
#define __GEOM2_H__

#include <cmath>

struct Vector {
  Vector() {}
  Vector(GLfloat _x, GLfloat _y) {
    x[0] = _x;
    x[1] = _y;
  }

  GLfloat x[2];
  GLfloat operator[](int i) { return x[i]; }
  GLfloat magnitude() { return sqrt(pow(x[0], 2) + pow(x[1], 2)); }
  Vector normalize() { return Vector(x[0]/magnitude(), x[1]/magnitude());   }
  GLfloat dot_prod(Vector other) { return x[0]*other[0] + x[1]*other[1]; }
};

inline GLfloat find_position(GLfloat acc, float elapsed_time,
                             GLfloat vi, GLfloat xi) {
  return .5*acc*(elapsed_time*elapsed_time) + vi*elapsed_time + xi;
}

inline GLfloat find_velocity(GLfloat acc, float elapsed_time, GLfloat vi) {
  return acc*elapsed_time + vi;
}

inline GLfloat find_accel(GLfloat v) {
  return drag_coeff*v;
}

inline GLfloat dist(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1) {
  return sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));
}

#endif
