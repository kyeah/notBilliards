#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __MAC__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

const double PI = 3.14159;
const double alpha = .6;
const double drag = -0.4;
const int window_width = 800;
const int window_height = 600;

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


#endif