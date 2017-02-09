//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Player.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Player.h"
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
// static read player
bool Player::read(istream &in, string &token, Group &group) {
    if (token == "Player") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing player opening brace");
        }
        in >> token;
        Player *player = new Player();
        group.push_back(player);
        ((Block *)player)->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// player colliders
void Player::colliders(const Game &game, vector<Shape *> &colliders) {
    colliders.push_back(this);
}

//------------------------------------------------------------------------------
