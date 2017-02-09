//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Physical.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Physical.h"
#include "Vectors.h"
#include "Reader.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read physical
bool Physical::read(istream &in, string &token) {
    if (token == "Physical") {
        in >> token;
        if (token != "{") {
            throw string("Error : Missing physical open brace");
        }
        in >> token;
        while (token != "}") {
            if (Reader::comment(in, token)) {
            }
            else if (token == "Position") {
                _position.readPosition(in);
                in >> token;
            }
            else if (token == "Velocity") {
                _velocity.readDirection(in);
                in >> token;
            }
            else if (token == "Axis") {
                _axis.readDirection(in);
                in >> token;
            }
            else if (token == "Angle") {
                in >> _angle >> token;
            }
            else if (token == "Spin") {
                in >> _spin >> token;
            }
            else if (token == "Density") {
                in >> _density >> token;
            }
            else if (token == "Restitution") {
                in >> _restitution >> token;
            }
            else if (token == "Friction") {
                in >> _friction >> token;
            }
            else if (token == "Damping") {
                in >> _damping >> token;
            }
            else {
                throw string("Error : Invalid physical attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// update physical
void Physical::update(const Game &/*game*/, double time) {
    _position += time * _velocity;
    _angle += time * _spin;
    _velocity = _velocity - (_damping * _velocity * time);
    _spin = _spin - (_damping * _spin * time);
}

//------------------------------------------------------------------------------
// render physical
void Physical::render(const Game &/*game*/) const {
    glTranslated(_position.x(), _position.y(), _position.z());
    glRotated(_angle, _axis.x(), _axis.y(), _axis.z());
}

//------------------------------------------------------------------------------
