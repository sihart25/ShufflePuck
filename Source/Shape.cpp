//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Shape.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Shape.h"
#include "Group.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Disc.h"
#include "Block.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read shape
bool Shape::read(istream &in, string &token, Group &group) {
    if (Cylinder::read(in, token, group)) {
        return true;
    }
    else if (Plane::read(in, token, group)) {
        return true;
    }
    else if (Disc::read(in, token, group)) {
        return true;
    }
    else if (Block::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
