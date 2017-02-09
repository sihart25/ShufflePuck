//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePost Assessment
// Post.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Post.h"
#include "Group.h"
#include "Reader.h"
#include "Block.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read post
bool Post::read(istream &in, string &token, Group &group) {
    if (token == "Post") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing post opening brace");
        }
        in >> token;
        Post *post = new Post();
        group.push_back(post);
        ((Cylinder *)post)->read(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// post obstacles
void Post::obstacles(const Game &game, vector<Shape *> &obstacles) {
    obstacles.push_back(this);
}

//------------------------------------------------------------------------------
