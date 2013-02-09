#include <math.h>
#include <iostream>

#include "./ball.h"
#include "./common.h"
#include "./geom2.h"

using namespace std;

// Handy ball class implementation

Ball::Ball(GLfloat _x, GLfloat _y, GLint _r, Color _c): radius(_r), c(_c) { 
  x[0] = _x;
  x[1] = _y;
  v[0] = v[1] = 0;
  a[0] = a[1] = 0;
  speed = .1;
}


GLfloat find_velocity(GLfloat acc, float elapsed_time) {
  return acc*elapsed_time;
}

GLfloat find_position(GLfloat acc, float elapsed_time, GLfloat vi) {
   return .5*acc*(elapsed_time*elapsed_time) + vi*elapsed_time;
}

GLfloat find_accel(GLfloat v) {
  return drag*v;
}

void Ball::draw() {
  glBegin(GL_TRIANGLE_FAN);
  for(int angle = 0; angle < 360; angle += 5) {
    int xn = x[0] + radius*sin(PI*angle/180);
    int yn = x[1] + radius*cos(PI*angle/180);
    glColor3fv(c);
    glVertex2f(xn, yn);
  }
  glEnd();
}



void Ball::update(float elapsed_time) {
  for(int i = 0; i < 2; i++) {
    x[i] += find_position(a[i], elapsed_time, v[i]);
    v[i] += find_velocity(a[i], elapsed_time);    
    a[i] = find_accel(v[i]);
  }

  if (x[0] < 0 || x[0] > window_width) v[0] *= -1;
  if (x[1] < 0 || x[1] > window_height) v[1] *= -1; 
  

  cout << "vx = " << v[0] << endl;
  cout << "vy = " << v[1] << endl;
  cout << x[0] << endl;
  cout << x[1] << endl;
}
