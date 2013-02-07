#include <math.h>

#include "./ball.h"
#include "./common.h"
#include "./geom2.h"

// Handy ball class implementation

Ball::Ball(GLint _x, GLint _y, GLint _r, Color _c): radius(_r), c(_c) { 
  x[0] = _x;
  x[1] = _y;
  velocity = 0;
}

void Ball::draw() {
  for(int angle = 0; angle < 360; angle += 5) {
    int xn = x[0] + radius*sin(PI*angle/180);
    int yn = x[1] + radius*cos(PI*angle/180);
    glColor3fv(c);
    glVertex2f(xn, yn);
  }
}
