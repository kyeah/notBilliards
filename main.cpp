#include <math.h>
#include <iostream>
#include <vector>

#include "./ball.h"
#include "./common.h"
#include "./geom2.h"

using namespace std;

const int window_width = 800;
const int window_height = 600;

Ball cueBall = Ball(0,0, 20, kBlue);
Ball testBall = Ball(1,1, 20, kRed);

void Init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-400.0, 400.0, -300.0, 300.0);
  glMatrixMode(GL_MODELVIEW);
}

void Display() {
  glClearColor(0,1,0,0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_TRIANGLE_FAN);
  cueBall.draw();
  glEnd();

  glFlush();
  glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y) {
  if (button = GLUT_LEFT_BUTTON) {
    if (state = GLUT_DOWN) {

    } //else if (state = GLUT_MOVE) {

     else if (state = GLUT_UP) {

    }
  }

  glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
  switch(key) {
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
  glutKeyboardFunc(Keyboard);
  Init();
  glutMainLoop();
  
}
