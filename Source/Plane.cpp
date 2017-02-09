//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Plane.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Plane.h"
#include "Group.h"
#include "Reader.h"
#include "Vectors.h"
#include "Constants.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read plane
bool Plane::read(istream &in, string &token, Group &group) {
    if (token == "Plane") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing plane opening brace");
        }
        in >> token;
        Plane *plane = new Plane();
        group.push_back(plane);
        plane->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read plane
void Plane::read(istream &in, string &token) {
    while (token != CLOSING_BRACE) {
        if (Reader::comment(in, token)) {
        }
        else if (_material.read(in, token)) {
        }
        else if (_physical.read(in, token)) {
        }
        else if (token == "Width") {
            in >> _width >> token;
        }
        else if (token == "Height") {
            in >> _height >> token;
        }
        else if (token == "Left") {
            in >> _left >> token;
        }
        else if (token == "Right") {
            in >> _right >> token;
        }
        else if (token == "Bottom") {
            in >> _bottom >> token;
        }
        else if (token == "Top") {
            in >> _top >> token;
        }
        else if (token == "Rows") {
            in >> _rows >> token;
        }
        else if (token == "Columns") {
            in >> _columns >> token;
        }
        else {
            throw string("Error : Invalid plane attribute = " + token);
        }
    }
    in >> token;
}

//------------------------------------------------------------------------------
// render plane
void Plane::render(const Game &game) const {
    glPushMatrix();
    _material.render(game);
    _physical.render(game);
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    double width = _width / (double)_columns;
    double height = _height / (double)_rows;
    double widthTexture = (_right - _left) / (double)_columns;
    double heightTexture = (_top - _bottom) / (double)_rows;
    for (int row = 0; row < _rows; row++) {
        double bottom = -0.5 * _height + (double)row * height;
        double top = bottom + height;
        double bottomTexture = _bottom + (double)row * heightTexture;
        double topTexture = bottomTexture + heightTexture;
        for (int column = 0; column < _columns; column++) {
            double left = -0.5 * _width + (double)column * width;
            double right = left + width;
            double leftTexture = _left + (double)column * widthTexture;
            double rightTexture = leftTexture + widthTexture;
            glTexCoord2d(leftTexture, bottomTexture);
            glVertex3d(left, bottom, 0.0);
            glTexCoord2d(rightTexture, bottomTexture);
            glVertex3d(right, bottom, 0.0);
            glTexCoord2d(rightTexture, topTexture);
            glVertex3d(right, top, 0.0);
            glTexCoord2d(leftTexture, topTexture);
            glVertex3d(left, top, 0.0);
        }
    }
    glEnd();
    glPopMatrix();
}

//------------------------------------------------------------------------------
