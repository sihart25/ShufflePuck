//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Disc.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Disc.h"
#include "Group.h"
#include "Reader.h"
#include "Constants.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read disc
bool Disc::read(istream &in, string &token, Group &group) {
    if (token == "Disc") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing disc opening brace");
        }
        in >> token;
        Disc *disc = new Disc();
        group.push_back(disc);
        disc->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read disc
void Disc::read(istream &in, string &token) {
    while (token != CLOSING_BRACE) {
        if (Reader::comment(in, token)) {
        }
        else if (_material.read(in, token)) {
        }
        else if (_physical.read(in, token)) {
        }
        else if (token == "Radius") {
            in >> _radius >> token;
        }
        else if (token == "Rows") {
            in >> _rows >> token;
        }
        else if (token == "Columns") {
            in >> _columns >> token;
        }
        else {
            throw string("Error : Invalid disc attribute = " + token);
        }
    }
    in >> token;
}

//------------------------------------------------------------------------------
// render disc
void Disc::render(const Game &game) const {
    glPushMatrix();
    _material.render(game);
    _physical.render(game);
    GLUquadricObj *disc = gluNewQuadric();
    gluQuadricDrawStyle(disc, GLU_FILL);
    gluQuadricNormals(disc, GLU_FLAT);
    gluQuadricTexture(disc, GL_TRUE);
    gluDisk(disc, 0.0, _radius, _columns, _rows);
    gluDeleteQuadric(disc);
    glPopMatrix();
}

//------------------------------------------------------------------------------
