#include <math.h>

#include "./ball.h"
#include "./common.h"
#include "./geom2.h"


Ball::Ball(GLfloat _x, GLfloat _y,
           GLint _r, Color _c, bool _solid): radius(_r), c(_c), solid(_solid) {
  x[0] = _x;
  x[1] = _y;
  v = Vector(0, 0);
  a[0] = a[1] = 0;
  mass = 1;
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

  if (solid) {
    glBegin(GL_TRIANGLE_FAN);
    for (int angle = 0; angle < 360; angle += 5) {
      int xn = x[0] + (radius/2)*sin(PI*angle/180);
      int yn = x[1] + (radius/2)*cos(PI*angle/180);
      glColor3f(1, 1, 1);
      glVertex2f(xn, yn);
    }
  }

  glEnd();
}

void Ball::update(float elapsed_time) {
  for (int i = 0; i < 2; i++) {
    x[i] = find_position(a[i], elapsed_time, v[i], x[i]);
    v.x[i] = find_velocity(a[i], elapsed_time, v[i]);
    a[i] = find_accel(v[i]);
  }

  checkBounds();
}

void Ball::checkBounds() {
  // Horizontal Bounds
  if (x[0] - radius < 25) {
    x[0] = radius + 25;
    v.x[0] = abs(v.x[0]);
  } else if (x[0] + radius > window_width - 25) {
     x[0] = window_width - 25 - radius;
    v.x[0] = -abs(v.x[0]);
  }

  // Vertical Bounds
  if (x[1] - radius < 25) {
     x[1] = radius + 25;
    v.x[1] = abs(v[1]);
  } else if (x[1] + radius > window_height - 25) {
     x[1] = window_height - 25 - radius;
    v.x[1] = -abs(v.x[1]);
  }
}

bool Ball::collide(Ball *other) {
  return dist(x[0], x[1], other->x[0], other->x[1]) <= radius + other->radius;
}

void Ball::setVelocity(GLfloat vx, GLfloat vy) {
  v.x[0] = vx;
  v.x[1] = vy;

  a[0] = find_accel(v.x[0]);
  a[1] = find_accel(v.x[1]);
}

void Ball::elasticCollision(Ball *other) {
  GLfloat position[2], velocity[2];
  GLfloat dot, d, a;

  position[0] = other->x[0] - x[0];
  position[1] = other->x[1] - x[1];
  velocity[0] = other->v.x[0] - v.x[0];
  velocity[1] = other->v.x[1] - v.x[1];

  dot = velocity[0]*position[0] + velocity[1]*position[1];

  if (dot <= 0) {
    a = position[1]/position[0];
    d = -2*(velocity[0] + (a*velocity[1]))/((1 + a*a)*2);
    other->v.x[0] = other->v.x[0] + d;
    other->v.x[1] = other->v.x[1] + a*d;
    v.x[0] = v.x[0] - d;
    v.x[1] = v.x[1] - a*d;
  }
}

