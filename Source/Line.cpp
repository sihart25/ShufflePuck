//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShuffleLine Assessment
// Line.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Line.h"
#include "Group.h"
#include "Reader.h"
#include "Block.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read line
bool Line::read(istream &in, string &token, Group &group) {
    if (token == "Line") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing line opening brace");
        }
        in >> token;
        Line *line = new Line();
        group.push_back(line);
        ((Block *)line)->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// line obstacles
void Line::obstacles(const Game &game, vector<Shape *> &obstacles) {
    obstacles.push_back(this);
}

//------------------------------------------------------------------------------
