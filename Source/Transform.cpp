//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Transform.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Transform.h"
#include "Group.h"
#include "Reader.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read transform
bool Transform::read(istream &in, string &token, Group &group) {
    if (token == "Transform") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing transform opening brace");
        }
        in >> token;
        Transform *transform = new Transform();
        group.push_back(transform);
        transform->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read transform
void Transform::read(istream &in, string &token) {
    while (token != CLOSING_BRACE) {
        if (Reader::comment(in, token)) {
        }
        else if (token == "Translate") {
            _translate.readDirection(in);
            in >> token;
        }
        else if (token == "Axis") {
            _axis.readDirection(in);
            in >> token;
        }
        else if (token == "Angle") {
            in >> _angle >> token;
        }
        else if (token == "Scale") {
            _scale.readDirection(in);
            in >> token;
        }
        else {
            throw string("Error : Invalid transform attribute = " + token);
        }
    }
    in >> token;
}

//------------------------------------------------------------------------------
// render this transform
void Transform::render(const Game &/*game*/) const {
    glTranslated(_translate.x(), _translate.y(), _translate.z());
    glRotated(_angle, _axis.x(), _axis.y(), _axis.z());
    glScaled(_scale.x(), _scale.y(), _scale.z());
}

//------------------------------------------------------------------------------
