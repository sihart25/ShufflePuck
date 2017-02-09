//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Camera.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <GL/glut.h>
#pragma hdrstop
#include "Camera.h"
#include "Group.h"
#include "Game.h"
#include "Reader.h"
#include "Vectors.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read camera
bool Camera::read(istream &in, string &token, Group &group) {
    if (token == "Camera") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing camera opening brace");
        }
        in >> token;
        Camera *camera = new Camera();
        group.push_back(camera);
        camera->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read camera
void Camera::read(istream &in, string &token) {
    while (token != CLOSING_BRACE) {
        if (Reader::comment(in, token)) {
        }
        else if (token == "Position") {
            _position.readPosition(in);
            in >> token;
        }
        else if (token == "Direction") {
            _direction.readDirection(in);
            in >> token;
        }
        else if (token == "Up") {
            _up.readDirection(in);
            in >> token;
        }
        else if (token == "FieldOfView") {
            in >> _fieldOfView >> token;
        }
        else {
            throw string("Error : Invalid camera attribute = " + token);
        }
    }
    in >> token;
}

//------------------------------------------------------------------------------
// transform by this camera
void Camera::render(const Game &game) const {
    const double NEAR_CLIP = 0.01;
    const double FAR_CLIP = 100.0;
    const double DISTANCE = 3.0;
    const double SEPARATION = 0.15;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double height = tan(0.5 * _fieldOfView * DEG_TO_RAD) * 2.0 * DISTANCE;
    double width = height * (double)glutGet(GLUT_WINDOW_WIDTH) / (double)glutGet(GLUT_WINDOW_HEIGHT);
    if ((game.key() == "LeftView") || (game.key() == "RightView")) {
        width *= 0.5;
    }
    double left = -0.5 * width;
    if (game.key() == "LeftView") {
        left = -0.5 * SEPARATION - width;
    }
    else if (game.key() == "RightView") {
        left = 0.5 * SEPARATION;
    }
    else if (game.key() == "LeftBufferView") {
        left = 0.5 * SEPARATION - 0.5 * width;
    }
    else if (game.key() == "RightBufferView") {
        left = -0.5 * SEPARATION - 0.5 * width;
    }
    double right = left + width;
    double bottom = -0.5 * height;
    double top = bottom + height;
    left *= NEAR_CLIP / DISTANCE;
    right *= NEAR_CLIP / DISTANCE;
    bottom *= NEAR_CLIP / DISTANCE;
    top *= NEAR_CLIP / DISTANCE;
    glFrustum(left, right, bottom, top, NEAR_CLIP, FAR_CLIP);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (game.key() == "LeftView") {
        glRotated(atan2(0.5 * SEPARATION + 0.5 * width, DISTANCE) * RAD_TO_DEG, 0.0, 1.0, 0.0);
        gluLookAt(0.5 * SEPARATION, 0.0, 0.0, 0.0, 0.0, -DISTANCE, 0.0, 1.0, 0.0);
    }
    else if (game.key() == "RightView") {
        glRotated(-atan2(0.5 * SEPARATION + 0.5 * width, DISTANCE) * RAD_TO_DEG, 0.0, 1.0, 0.0);
        gluLookAt(-0.5 * SEPARATION, 0.0, 0.0, 0.0, 0.0, -DISTANCE, 0.0, 1.0, 0.0);
    }
    else if (game.key() == "LeftBufferView") {
        glRotated(-atan2(0.5 * SEPARATION, DISTANCE) * RAD_TO_DEG, 0.0, 1.0, 0.0);
        gluLookAt(-0.5 * SEPARATION, 0.0, 0.0, 0.0, 0.0, -DISTANCE, 0.0, 1.0, 0.0);
    }
    else if (game.key() == "RightBufferView") {
        glRotated(atan2(0.5 * SEPARATION, DISTANCE) * RAD_TO_DEG, 0.0, 1.0, 0.0);
        gluLookAt(0.5 * SEPARATION, 0.0, 0.0, 0.0, 0.0, -DISTANCE, 0.0, 1.0, 0.0);
    }
    gluLookAt(_position.x(), _position.y(), _position.z(),
        _position.x() + _direction.x(), _position.y() + _direction.y(), _position.z() + _direction.z(),
        _up.x(), _up.y(), _up.z());
}

//------------------------------------------------------------------------------
