#include <math.h>
#include <iostream>
#include <vector>

#include "./ball.h"
#include "./common.h"
// #include "./geom2.h"

using namespace std;

float last_time = glutGet(GLUT_ELAPSED_TIME);

Ball cueBall = Ball((GLfloat)window_width/2,
                    (GLfloat)window_height/2,
                    20, kBlue);
vector<Ball> balls;
GLint mouse_down[2];
bool draw_line = false;

void Init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, window_width, window_height, 0);
  glMatrixMode(GL_MODELVIEW);

  balls.push_back(Ball(100.0, 100.0, 20, kRed));
  balls.push_back(Ball(-100.0, -100.0, 20, kRed));
}

void idle(void) {
  float present_time = glutGet(GLUT_ELAPSED_TIME);
  float elapsed_time = .001*(present_time - last_time);
  cueBall.update(elapsed_time);

  for (int i = 0; i < balls.size(); i++)
    balls[i].update(elapsed_time);

  last_time = present_time;
  glutPostRedisplay();
}


void Display() {
  glClearColor(0, 1, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  cueBall.draw();

  for (int i = 0; i < balls.size(); i++)
    balls[i].draw();

  if (draw_line) {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(cueBall.x[0], cueBall.x[1]);
    glVertex2f(mouse_down[0], mouse_down[1]);
    glEnd();
  }

  glFlush();
  glutSwapBuffers();
}


void Mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      mouse_down[0] = x;
      mouse_down[1] = y;
      draw_line = true;
      }
    if (state == GLUT_UP) {
      cueBall.v[0] = velocity_coeff * (cueBall.x[0] - mouse_down[0]);
      cueBall.v[1] = velocity_coeff * (cueBall.x[1] - mouse_down[1]);
      cueBall.a[0] = drag_coeff*cueBall.v[0];
      cueBall.a[1] = drag_coeff*cueBall.v[1];
      draw_line = false;
    }
  }

  glutPostRedisplay();
}

void MouseMotion(int x, int y) {
  mouse_down[0] = x;
  mouse_down[1] = y;

  glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'q':
    exit(EXIT_SUCCESS);
    break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("BILLIARDS!!!!");
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMotion);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc(idle);
  Init();
  glutMainLoop();
}
