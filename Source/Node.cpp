//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Node.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Node.h"
#include "Group.h"
#include "Camera.h"
#include "Transform.h"
#include "Light.h"
#include "Shape.h"
#include "Reference.h"
#include "Sound.h"
#include "Texture.h"
#include "Screen.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read node
bool Node::read(istream &in, string &token, Group &group) {
    if (Reader::comment(in, token)) {
        return true;
    }
    else if (Group::read(in, token, group)) {
        return true;
    }
    else if (Screen::read(in, token, group)) {
        return true;
    }
    else if (Camera::read(in, token, group)) {
        return true;
    }
    else if (Transform::read(in, token, group)) {
        return true;
    }
    else if (Light::read(in, token, group)) {
        return true;
    }
    else if (Shape::read(in, token, group)) {
        return true;
    }
    else if (Reference::read(in, token, group)) {
        return true;
    }
    else if (Sound::read(in, token, group)) {
        return true;
    }
    else if (Texture::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
