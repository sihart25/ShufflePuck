//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Reference.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Reference.h"
#include "Group.h"
#include "Reader.h"
#include "Label.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read reference
bool Reference::read(istream &in, string &token, Group &group) {
    if (token == "Reference") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing reference opening brace");
        }
        in >> token;
        Reference *reference = new Reference();
        group.push_back(reference);
        reference->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read reference
void Reference::read(istream &in, string &token) {
    while (token != CLOSING_BRACE) {
        if (Reader::comment(in, token)) {
        }
        else if (token == "Label") {
            in >> _label >> token;
        }
        else if (token == "Index") {
            in >> _index >> token;
        }
        else {
            throw string("Error : Invalid reference attribute = " + token);
        }
    }
    in >> token;
}

//------------------------------------------------------------------------------
// reference colliders
void Reference::colliders(const Game &game, vector<Shape *> &colliders) {
    game.find(_label, _index)->colliders(game, colliders);
}

//------------------------------------------------------------------------------
// reference obstacles
void Reference::obstacles(const Game &game, vector<Shape *> &obstacles) {
    game.find(_label, _index)->obstacles(game, obstacles);
}

//------------------------------------------------------------------------------
// update reference
void Reference::update(const Game &game, double time) {
    game.find(_label, _index)->update(game, time);
}

//------------------------------------------------------------------------------
// render reference
void Reference::render(const Game &game) const {
    game.find(_label, _index)->render(game);
}

//------------------------------------------------------------------------------
