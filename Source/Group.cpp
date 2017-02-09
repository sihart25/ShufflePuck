//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Group.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>
#pragma hdrstop
#include "Group.h"
#include "Light.h"
#include "Shape.h"
#include "Node.h"
#include "Reader.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// erase group
void Group::erase() {
    if (_owner) {
        for (vector<Node *>::iterator node = _nodes.begin(); node != _nodes.end(); ++node) {
            delete *node;
        }
    }
    _nodes.clear();
}

//------------------------------------------------------------------------------
// copy group
void Group::copy(const Group &group) {
    _owner = group._owner;
    for (vector<Node *>::const_iterator node = group._nodes.begin(); node != group._nodes.end(); ++node) {
        _nodes.push_back((*node)->clone());
    }
}

//------------------------------------------------------------------------------
// static read group
bool Group::read(istream &in, string &token, Group &group) {
    if (token == "Group") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing group opening brace");
        }
        in >> token;
        Group *nestedGroup = new Group();
        group.push_back(nestedGroup);
        while (token != CLOSING_BRACE) {
            if (Node::read(in, token, *nestedGroup)) {}
            else {
                throw string("Error : Invalid group attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render group
void Group::render(const Game &game) const {
    glPushMatrix();
    for (vector<Node *>::const_iterator node = _nodes.begin(); node != _nodes.end(); node++) {
        (*node)->render(game);
    }
    glPopMatrix();
}

//------------------------------------------------------------------------------
// update group
void Group::update(const Game &game, double time) {
    for (vector<Node *>::const_iterator node = _nodes.begin(); node != _nodes.end(); node++) {
        (*node)->update(game, time);
    }
}

//------------------------------------------------------------------------------
// group colliders
void Group::colliders(const Game &game, vector<Shape *> &colliders) {
    for (vector<Node *>::const_iterator node = _nodes.begin(); node != _nodes.end(); node++) {
        (*node)->colliders(game, colliders);
    }
}

//------------------------------------------------------------------------------
// group obstacles
void Group::obstacles(const Game &game, vector<Shape *> &obstacles) {
    for (vector<Node *>::const_iterator node = _nodes.begin(); node != _nodes.end(); node++) {
        (*node)->obstacles(game, obstacles);
    }
}

//------------------------------------------------------------------------------
