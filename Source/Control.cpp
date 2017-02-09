//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Control.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#ifdef WIN32
#include <sstream>
#endif
#include <iomanip>
#include <ctime>
#include <GL/glut.h>
#pragma hdrstop
#include "Control.h"
#include "Sound.h"
#include "Reference.h"
#include "Transform.h"
#include "Game.h"
#include "Label.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// initialize
void Control::initialize(int *argc, char **argv) {
    if (*argc != 2) {
        _filename = string("../Data/Game.txt");
    }
    else {
        _filename = argv[1];
    }
    Sound::init(argc, argv);
    _font.init();
    glShadeModel(GL_SMOOTH);
    GLfloat ambient[] = {0.0, 0.0, 0.0, 0.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glFogi(GL_FOG_MODE, GL_EXP2);
    glEnable(GL_FOG);
    glDrawBuffer(GL_BACK_LEFT);
    start();
}

//------------------------------------------------------------------------------
// menu
void Control::menu() const {
    cout << "escape                 exit" << endl;
    cout << "space                  restart" << endl;
    cout << "f1                     player view" << endl;
    cout << "f2                     aerial view" << endl;
    cout << "f3                     puck view" << endl;
    cout << "f4                     next puck view" << endl;
    cout << "f5                     player inset view" << endl;
    cout << "f6                     aerial inset view" << endl;
    cout << "f7                     puck inset view" << endl;
    cout << "f8                     toggle score" << endl;
    cout << "f9                     cross-eyed view" << endl;
    cout << "f10                    stereo view" << endl;
    cout << "f11                    left view" << endl;
    cout << "f12                    right view" << endl;
    cout << "1                      toggle reflections" << endl;
    cout << "2                      toggle shadows" << endl;
    cout << "3                      toggle fog" << endl;
    cout << "4                      toggle wireframe" << endl;
    cout << "5                      toggle sound" << endl;
    cout << "6                      doh sound" << endl;
    cout << "7                      ahhhhh sound" << endl;
    cout << "8                      woosh sound" << endl;
    cout << "insert                 add puck" << endl;
    cout << "delete                 remove puck" << endl;
    cout << "left, right, mouse     rotate" << endl;
    cout << "down, up, mouse        move" << endl;
    cout << "page down, left mouse  home player" << endl;
    cout << "page up, right mouse   away player" << endl;
}

//------------------------------------------------------------------------------
// start
void Control::start() {
    _game = Game();
    _game.read(_filename);
    _game.start();
}

//------------------------------------------------------------------------------
// display
void Control::display() {
    _game.play(60.0);
    #ifdef WIN32
    ostringstream oss;
    oss << setiosflags(ios::fixed) << setprecision(2);
    oss << "ShufflePuck ... " << _rate << " fps";
    glutSetWindowTitle(oss.str().c_str());
    #else
    glutSetWindowTitle("ShufflePuck");
    #endif
    glPolygonMode(GL_FRONT_AND_BACK, !_wireframe ? GL_FILL : GL_LINE);
    if (_fog) {
        glEnable(GL_FOG);
    }
    else {
        glDisable(GL_FOG);
    }
    _game.render("Screen", _reflections, _shadows);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    switch (_view) {
        case PLAYER: {
            _game.render("PlayerView", _reflections, _shadows);
            break;
        }
        case AERIAL: {
            _game.render("AerialView", _reflections, _shadows);
            break;
        }
        case PUCK: {
            _game.render("PuckView", _reflections, _shadows);
            break;
        }
        case CROSS: {
            const double border = 0.01;
            glViewport((int)((1.0 + border) * glutGet(GLUT_WINDOW_WIDTH) / 2),
                (int)(border * glutGet(GLUT_WINDOW_HEIGHT)),
                (int)((1.0 - 1.5 * border) * glutGet(GLUT_WINDOW_WIDTH) / 2),
                (int)((1.0 - 2.0 * border) * glutGet(GLUT_WINDOW_HEIGHT)));
            _game.render("RightView", _reflections, _shadows);
            glViewport((int)(border * glutGet(GLUT_WINDOW_WIDTH) / 2),
                (int)(border * glutGet(GLUT_WINDOW_HEIGHT)),
                (int)((1.0 - 1.5 * border) * glutGet(GLUT_WINDOW_WIDTH) / 2),
                (int)((1.0 - 2.0 * border) * glutGet(GLUT_WINDOW_HEIGHT)));
            _game.render("LeftView", _reflections, _shadows);
            break;
        }
        case LEFT: {
            _game.render("LeftBufferView", _reflections, _shadows);
            break;
        }
        case RIGHT: {
            _game.render("RightBufferView", _reflections, _shadows);
            break;
        }
        case STEREO: {
            if (glutGet(GLUT_WINDOW_STEREO) == 1) {
                glDrawBuffer(GL_BACK_RIGHT);
                _game.render("RightBufferView", _reflections, _shadows);
                glDrawBuffer(GL_BACK_LEFT);
                _game.render("LeftBufferView", _reflections, _shadows);
            }
            break;
        }
    }
    if (_view != CROSS && _inset != NONE) {
        glViewport(glutGet(GLUT_WINDOW_WIDTH) * 3 / 4, glutGet(GLUT_WINDOW_HEIGHT) * 3 / 4,
            glutGet(GLUT_WINDOW_WIDTH) / 4, glutGet(GLUT_WINDOW_HEIGHT) / 4);
        glScissor(glutGet(GLUT_WINDOW_WIDTH) * 3 / 4, glutGet(GLUT_WINDOW_HEIGHT) * 3 / 4,
            glutGet(GLUT_WINDOW_WIDTH) / 4, glutGet(GLUT_WINDOW_HEIGHT) / 4);
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);
        switch (_inset) {
            case PLAYER: {
                _game.render("PlayerView", _reflections, _shadows);
                break;
            }
            case AERIAL: {
                _game.render("AerialView", _reflections, _shadows);
                break;
            }
            case PUCK: {
                _game.render("PuckView", _reflections, _shadows);
                break;
            }
        }
    }
    if (_score) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        ostringstream score;
        score << _game.score(0) << "-" << _game.score(1);
        _font.set(score.str(), false, 0.0, -5.5, 0.4, 0.4);
        _font.render(_game);
    }
    glutSwapBuffers();
    _count++;
}

//------------------------------------------------------------------------------
// reshape
void Control::reshape(int width, int height) {
}

//------------------------------------------------------------------------------
// keyboard
void Control::keyboard(unsigned char key, int /*x*/, int /*y*/) {
    const int DELETE = 0x7F;
    const int ESCAPE = 0x1B;
    switch (key) {
        case ' ': {
            start();
            break;
        }
        case '1': {
            _reflections = !_reflections;
            break;
        }
        case '2': {
            _shadows = !_shadows;
            break;
        }
        case '3': {
            _fog = !_fog;
            break;
        }
        case '4': {
            _wireframe = !_wireframe;
            break;
        }
        case '5': {
            Sound::enable(!Sound::enable());
            break;
        }
        case '6': {
            ((Sound *)(_game.find("Doh")->nodes()[0]))->volume(1.0);
            _game.find("Doh")->render(_game);
            break;
        }
        case '7': {
            ((Sound *)(_game.find("Woohoo")->nodes()[0]))->volume(1.0);
            _game.find("Woohoo")->render(_game);
            break;
        }
        case '8': {
            ((Sound *)(_game.find("Woosh")->nodes()[0]))->volume(1.0);
            _game.find("Woosh")->render(_game);
            break;
        }
        case DELETE: {
            _game.removePuck();
            break;
        }
        case ESCAPE: {
            glutDestroyWindow(glutGetWindow());
            delete this;
            Sound::close();
            exit(0);
        }
        default: {
            return;
        }
    }
}

//------------------------------------------------------------------------------
// special
void Control::special(int key, int /*x*/, int /*y*/) {
    const double ANGLE_INCREMENT = 100.0;
    const double POSITION_INCREMENT = 10.0;
    switch (key) {
        case GLUT_KEY_F1: {
            _view = PLAYER;
            break;
        }
        case GLUT_KEY_F2: {
            _view = AERIAL;
            break;
        }
        case GLUT_KEY_F3: {
            _view = PUCK;
            break;
        }
        case GLUT_KEY_F4: {
            _game.nextPuck();
            break;
        }
        case GLUT_KEY_F5: {
            if (_inset == PLAYER) {
                _inset = NONE;
            }
            else {
                _inset = PLAYER;
            }
            break;
        }
        case GLUT_KEY_F6: {
            if (_inset == AERIAL) {
                _inset = NONE;
            }
            else {
                _inset = AERIAL;
            }
            break;
        }
        case GLUT_KEY_F7: {
            if (_inset == PUCK) {
                _inset = NONE;
            }
            else {
                _inset = PUCK;
            }
            break;
        }
        case GLUT_KEY_F8: {
            _score = !_score;
            break;
        }
        case GLUT_KEY_F9: {
            _view = CROSS;
            break;
        }
        case GLUT_KEY_F10: {
            if (glutGet(GLUT_WINDOW_STEREO) == 1) {
                _view = STEREO;
            }
            else {
                _view = CROSS;
            }
            break;
        }
        case GLUT_KEY_F11: {
            _view = LEFT;
            break;
        }
        case GLUT_KEY_F12: {
            _view = RIGHT;
            break;
        }
        case GLUT_KEY_LEFT: {
            _game.movePlayer(0.0, ANGLE_INCREMENT);
            break;
        }
        case GLUT_KEY_RIGHT: {
            _game.movePlayer(0.0, -ANGLE_INCREMENT);
            break;
        }
        case GLUT_KEY_DOWN: {
            _game.movePlayer(-POSITION_INCREMENT, 0.0);
            break;
        }
        case GLUT_KEY_UP: {
            _game.movePlayer(POSITION_INCREMENT, 0.0);
            break;
        }
        case GLUT_KEY_PAGE_DOWN: {
            _game.player(0);
            break;
        }
        case GLUT_KEY_PAGE_UP: {
            _game.player(1);
            break;
        }
        case GLUT_KEY_INSERT: {
            _game.addPuck();
            break;
        }
    }
}

//------------------------------------------------------------------------------
// mouse
void Control::mouse(int button, int state, int x, int y) {
    _motionX = x;
    _motionY = y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _game.player(0);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        _game.player(1);
    }
}

//------------------------------------------------------------------------------
// motion
void Control::motion(int x, int y) {
    const double ANGLE_INCREMENT = 10.0;
    const double POSITION_INCREMENT = 1.0;
    _game.movePlayer((_motionY - y) * POSITION_INCREMENT, -(x - _motionX) * ANGLE_INCREMENT);
    _motionX = x;
    _motionY = y;
}

//------------------------------------------------------------------------------
// idle
void Control::idle() {
    glutPostRedisplay();
    const double INTERVAL = 1.0;
    double interval;
    clock_t now;
    now = clock();
    if ((interval = double(now - _then) / CLOCKS_PER_SEC) > INTERVAL) {
        _rate = (double)_count / interval;
        _then = now;
        _count = 0;
    }
}

//------------------------------------------------------------------------------
