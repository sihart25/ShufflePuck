//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Puck.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Puck.h"
#include "Group.h"
#include "Reader.h"
#include "Disc.h"
#include "Vectors.h"
#include "Constants.h"
#include "Game.h"
#include "Shape.h"
#include "Collision.h"
#include "Block.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read puck
bool Puck::read(istream &in, string &token, Group &group) {
    if (token == "Puck") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing puck opening brace");
        }
        in >> token;
        Puck *puck = new Puck();
        group.push_back(puck);
        ((Cylinder *)puck)->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// puck colliders
void Puck::colliders(const Game &game, vector<Shape *> &colliders) {
    colliders.push_back(this);
}

//------------------------------------------------------------------------------
