//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShuffleWall Assessment
// Wall.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Wall.h"
#include "Group.h"
#include "Reader.h"
#include "Block.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read wall
bool Wall::read(istream &in, string &token, Group &group) {
    if (token == "Wall") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing wall opening brace");
        }
        in >> token;
        Wall *wall = new Wall();
        group.push_back(wall);
        ((Block *)wall)->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// wall obstacles
void Wall::obstacles(const Game &game, vector<Shape *> &obstacles) {
    obstacles.push_back(this);
}

//------------------------------------------------------------------------------
