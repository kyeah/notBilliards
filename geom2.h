#ifndef __GEOM2_H__
#define __GEOM2_H__

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

#endif
