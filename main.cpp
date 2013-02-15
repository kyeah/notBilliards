#include <math.h>
#include <iostream>
#include <vector>

#include "./ball.h"
#include "./common.h"
#include "./geom2.h"

using namespace std;

enum { DRAW_NULL, DRAW_AIM, DRAW_SHOT };

vector<Ball> balls;
vector<Ball> scored;
vector<Ball> holes;
GLint mouse_down[2];
int draw_line = DRAW_NULL;
float shot_time = 0;
float last_time = glutGet(GLUT_ELAPSED_TIME);

Color colors[] = {kYellow, kBlue, kBrown, kViolet, kOrange, kGreen, kRed};

void TableSetup() {
  // Pocket Setup
  holes.push_back(Ball(15.0, 15.0, 25, kBlack, false));
  holes.push_back(Ball(15.0, window_height-15, 25, kBlack, false));
  holes.push_back(Ball(window_width/2, 5.0, 25, kBlack, false));
  holes.push_back(Ball(window_width/2, window_height-5, 25, kBlack, false));
  holes.push_back(Ball(window_width-15, 15.0, 25, kBlack, false));
  holes.push_back(Ball(window_width-15, window_height-18, 25, kBlack, false));

  // Cueball Setup
  balls.push_back(Ball(150, window_height/2, 15, kWhite, false));

  // 15-ball Billiards Setup
  int ball_num = 1;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < i + 1; j++) {
      if (ball_num < 8)
        balls.push_back(Ball(500+(30*i),
                             (window_height/2)-(30*i/2)+(32*j),
                             15, colors[(ball_num - 1)%7], true) );
      else if (ball_num == 8)
        balls.push_back(Ball(500+(30*i),
                             (window_height/2)-(30*i/2)+(31*j),
                             15, kBlack, false) );
      else
        balls.push_back(Ball(500+(30*i),
                             (window_height/2)-(30*i/2)+(31*j),
                             15, colors[(ball_num - 1)%7], false) );

      ball_num++;
    }
  }
}

void drawTable() {
  glColor3f(0.545098, 0.270588, 0.0745098);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0.0, 0.0);
  glVertex2f(20.0, 0.0);
  glVertex2f(20.0, window_height);
  glVertex2f(0.0, window_height);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(0.0, 0.0);
  glVertex2f(window_width, 0.0);
  glVertex2f(window_width, 20.0);
  glVertex2f(0.0, 20.0);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(window_width, 0.0);
  glVertex2f(window_width, window_height);
  glVertex2f(window_width - 20, window_height);
  glVertex2f(window_width - 20, .0);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(window_width, window_height);
  glVertex2f(window_width, window_height - 20);
  glVertex2f(0.0, window_height - 20);
  glVertex2f(0.0, window_height);
  glEnd();
}

void drawCueStick() {
  float tip_scale, end_scale;
  if (draw_line == DRAW_AIM) {
    tip_scale = .5;
    end_scale = 5;
  } else {
    tip_scale = .95;
    end_scale = 4;
  }

  glLineWidth(7);
  glColor3f(.647, .1647, .1647);

  glBegin(GL_LINES);
  glVertex2f(mouse_down[0] + tip_scale*(balls[0].x[0] - mouse_down[0]),
             mouse_down[1] + tip_scale*(balls[0].x[1] - mouse_down[1]));
  glVertex2f(mouse_down[0] - end_scale*(balls[0].x[0] - mouse_down[0]),
             mouse_down[1] - end_scale*(balls[0].x[1] - mouse_down[1]));
  glEnd();
}

void drawAimHelper() {
  glLineWidth(2);
  glColor3f(1, 1, 1);
  glLineStipple(1, 10);
  glEnable(GL_LINE_STIPPLE);

  glBegin(GL_LINES);
  glVertex2f(balls[0].x[0], balls[0].x[1]);
  glVertex2f(mouse_down[0] + 3*(balls[0].x[0] - mouse_down[0]),
             mouse_down[1] + 3*(balls[0].x[1] - mouse_down[1]));
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void Init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, window_width, window_height, 0);
  glMatrixMode(GL_MODELVIEW);

  TableSetup();
}

void score(int index) {
  for (int i = 0; i < holes.size(); i++) {
    if (balls[index].collide(&holes[i])) {
      balls[index].x[0] = holes[i].x[0];
      balls[index].x[1] = holes[i].x[1];
      balls[index].setVelocity(0, 0);
      scored.push_back(balls[index]);
      balls.erase(balls.begin()+index);
      break;
    }
  }
}

void idle(void) {
  float present_time = glutGet(GLUT_ELAPSED_TIME);
  float elapsed_time = .001*(present_time - last_time);

  for (int i = 0; i < balls.size(); i++) {
    if (i > 0) score(i);

    for (int j = i+1; j < balls.size(); j++) {
      if (balls[i].collide(&balls[j]))
        balls[i].elasticCollision(&balls[j]);
    }

    balls[i].update(elapsed_time);
  }

  last_time = present_time;
  glutPostRedisplay();
}

void Display() {
  glClearColor(0, 0.4, 0.1, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  drawTable();

  for (int i = 0; i < holes.size(); i++)
    holes[i].draw();
  for (int i = 0; i < balls.size(); i++)
    balls[i].draw();
  for (int i = 0; i < scored.size(); i++)
    scored[i].draw();

  if (draw_line == DRAW_SHOT && glutGet(GLUT_ELAPSED_TIME) - shot_time > 25) {
    draw_line = DRAW_NULL;
  } else if (draw_line != DRAW_NULL) {
    drawCueStick();
    drawAimHelper();
  }

  glFlush();
  glutSwapBuffers();
}


void Mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      mouse_down[0] = x;
      mouse_down[1] = y;
      draw_line = DRAW_AIM;
    }
    if (state == GLUT_UP) {
      balls[0].v.x[0] = velocity_coeff * (balls[0].x[0] - mouse_down[0]);
      balls[0].v.x[1] = velocity_coeff * (balls[0].x[1] - mouse_down[1]);
      balls[0].a[0] = drag_coeff*balls[0].v[0];
      balls[0].a[1] = drag_coeff*balls[0].v[1];
      draw_line = DRAW_SHOT;
      shot_time = glutGet(GLUT_ELAPSED_TIME);
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
  glutInitWindowPosition(300, 300);
  glutCreateWindow("BILLIARDS!!!!");
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMotion);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc(idle);
  Init();
  glutMainLoop();
}
