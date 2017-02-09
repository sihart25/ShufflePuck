//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Display.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cfloat>
#include <GL/glut.h>
#pragma hdrstop
#include "Display.h"
#include "Control.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
Control *Display::_control = 0;

//------------------------------------------------------------------------------
// initialize
void Display::initialize(int argc, char **argv) {
    try {
        // gluSphere and gluCylinder throw zero divide exceptions
        #ifdef WIN32
        _control87(MCW_EM, MCW_EM);
        #endif
        _control = new Control();
        // initialise OpenGL
        glutInit(&argc, argv);
        glutInitWindowPosition(0, 0);
        glutInitWindowSize(WIDTH, HEIGHT);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL | GLUT_STEREO);
        if (glutGet(GLUT_DISPLAY_MODE_POSSIBLE) == 0) {
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
        }
        if (glutGet(GLUT_DISPLAY_MODE_POSSIBLE) == 0) {
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH);
        }
        glutCreateWindow("ShufflePuck");
        glutDisplayFunc(Display::display);
        glutReshapeFunc(Display::reshape);
        glutKeyboardFunc(Display::keyboard);
        glutMouseFunc(Display::mouse);
        glutMotionFunc(Display::motion);
        glutSpecialFunc(Display::special);
        glutIdleFunc(Display::idle);
        // initialise control
        _control->menu();
        _control->initialize(&argc, argv);
        // call GLUT main loop
        glutMainLoop();
    }
    catch (...) {
        cout << "Error : Unknown exception caught in display" << endl;
    }
    delete _control;
}

//------------------------------------------------------------------------------
