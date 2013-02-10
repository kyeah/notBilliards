#include <math.h>
#include <iostream>  // REMOVE BEFORE TURNING IN

#include "./ball.h"
#include "./common.h"
#include "./geom2.h"

using namespace std;  // REMOVE BEFORE TURNING IN

Ball::Ball(GLfloat _x, GLfloat _y, GLint _r, Color _c): radius(_r), c(_c) {
  x[0] = _x;
  x[1] = _y;
  v[0] = v[1] = 0;
  a[0] = a[1] = 0;
}

void Ball::draw() {
  glBegin(GL_TRIANGLE_FAN);
  for (int angle = 0; angle < 360; angle += 5) {
    int xn = x[0] + radius*sin(PI*angle/180);
    int yn = x[1] + radius*cos(PI*angle/180);
    glColor3fv(c);
    glVertex2f(xn, yn);
  }
  glEnd();
}

void Ball::update(float elapsed_time) {
  for (int i = 0; i < 2; i++) {
    x[i] = find_position(a[i], elapsed_time, v[i], x[i]);
    v[i] = find_velocity(a[i], elapsed_time, v[i]);
    a[i] = find_accel(v[i]);
  }

  checkBounds();

  cout << "vx = " << v[0] << endl;
  cout << "vy = " << v[1] << endl;
  cout << x[0] << endl;
  cout << x[1] << endl;
}

void Ball::checkBounds() {
  // Horizontal Bounds
  if (x[0] - radius < 0) {
    x[0] = radius;
    v[0] = abs(v[0]);
  } else if (x[0] + radius > window_width) {
     x[0] = window_width - radius;
    v[0] = -abs(v[0]);
  }

  // Vertical Bounds
  if (x[1] - radius < 0) {
     x[1] = radius;
    v[1] = abs(v[1]);
  } else if (x[1] + radius > window_height) {
     x[1] = window_height - radius;
    v[1] = -abs(v[1]);
  }
}
