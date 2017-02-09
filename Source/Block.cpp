//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Block.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Block.h"
#include "Group.h"
#include "Reader.h"
#include "Disc.h"
#include "Vectors.h"
#include "Constants.h"
#include "Game.h"
#include "Shape.h"
#include "Collision.h"
#include "Cylinder.h"
#include "Player.h"
#include "Wall.h"
#include "Line.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read block
bool Block::read(istream &in, string &token, Group &group) {
    if (token == "Block") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing block opening brace");
        }
        in >> token;
        Block *block = new Block();
        group.push_back(block);
        block->read(in, token);
        return true;
    }
    else if (Player::read(in, token, group)) {
        return true;
    }
    else if (Wall::read(in, token, group)) {
        return true;
    }
    else if (Line::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read block
void Block::read(istream &in, string &token) {
    while (token != CLOSING_BRACE) {
        if (Reader::comment(in, token)) {
        }
        else if (_material.read(in, token)) {
        }
        else if (_physical.read(in, token)) {
        }
        else if (token == "Width") {
            in >> _width >> token;
        }
        else if (token == "Height") {
            in >> _height >> token;
        }
        else if (token == "Depth") {
            in >> _depth >> token;
        }
        else if (token == "Left") {
            in >> _left >> token;
        }
        else if (token == "Right") {
            in >> _right >> token;
        }
        else if (token == "Bottom") {
            in >> _bottom >> token;
        }
        else if (token == "Top") {
            in >> _top >> token;
        }
        else {
            throw string("Error : Invalid block attribute = " + token);
        }
    }
    in >> token;
}

//------------------------------------------------------------------------------
// render block
void Block::render(const Game &game) const {
    glPushMatrix();
    _material.render(game);
    _physical.render(game);
    glBegin(GL_QUADS);
    // front
    glNormal3d(0.0, 0.0, 1.0);
    glTexCoord2d(_left, _bottom);
    glVertex3d(-0.5 * _width, -0.5 * _height, 0.5 * _depth);
    glTexCoord2d(_right, _bottom);
    glVertex3d(0.5 * _width, -0.5 * _height, 0.5 * _depth);
    glTexCoord2d(_right, _top);
    glVertex3d(0.5 * _width, 0.5 * _height, 0.5 * _depth);
    glTexCoord2d(_left, _top);
    glVertex3d(-0.5 * _width, 0.5 * _height, 0.5 * _depth);
    // back
    glNormal3d(0.0, 0.0, -1.0);
    glTexCoord2d(_left, _bottom);
    glVertex3d(0.5 * _width, -0.5 * _height, -0.5 * _depth);
    glTexCoord2d(_right, _bottom);
    glVertex3d(-0.5 * _width, -0.5 * _height, -0.5 * _depth);
    glTexCoord2d(_right, _top);
    glVertex3d(-0.5 * _width, 0.5 * _height, -0.5 * _depth);
    glTexCoord2d(_left, _top);
    glVertex3d(0.5 * _width, 0.5 * _height, -0.5 * _depth);
    // right
    glNormal3d(1.0, 0.0, 0.0);
    glTexCoord2d(0.5 * (_left + _right) - 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, -0.5 * _height, -0.5 * _depth);
    glTexCoord2d(0.5 * (_left + _right) + 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, 0.5 * _height, -0.5 * _depth);
    glTexCoord2d(0.5 * (_left + _right) + 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, 0.5 * _height, 0.5 * _depth);
    glTexCoord2d(0.5 * (_left + _right) - 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, -0.5 * _height, 0.5 * _depth);
    // left
    glNormal3d(-1.0, 0.0, 0.0);
    glTexCoord2d(0.5 * (_left + _right) - 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, 0.5 * _height, -0.5 * _depth);
    glTexCoord2d(0.5 * (_left + _right) + 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, -0.5 * _height, -0.5 * _depth);
    glTexCoord2d(0.5 * (_left + _right) + 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, -0.5 * _height, 0.5 * _depth);
    glTexCoord2d(0.5 * (_left + _right) - 0.5 * (_right - _left) * _height / _width,
        0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, 0.5 * _height, 0.5 * _depth);
    // top
    glNormal3d(0.0, 1.0, 0.0);
    glTexCoord2d(_left, 0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, 0.5 * _height, -0.5 * _depth);
    glTexCoord2d(_right, 0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, 0.5 * _height, -0.5 * _depth);
    glTexCoord2d(_right, 0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, 0.5 * _height, 0.5 * _depth);
    glTexCoord2d(_left, 0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, 0.5 * _height, 0.5 * _depth);
    // bottom
    glNormal3d(0.0, -1.0, 0.0);
    glTexCoord2d(_left, 0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, -0.5 * _height, -0.5 * _depth);
    glTexCoord2d(_right, 0.5 * (_bottom + _top) - 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, -0.5 * _height, -0.5 * _depth);
    glTexCoord2d(_right, 0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(0.5 * _width, -0.5 * _height, 0.5 * _depth);
    glTexCoord2d(_left, 0.5 * (_bottom + _top) + 0.5 * (_top - _bottom) * _depth / _height);
    glVertex3d(-0.5 * _width, -0.5 * _height, 0.5 * _depth);
    glEnd();
    glPopMatrix();
}

//------------------------------------------------------------------------------
// block collision with block
bool Block::block(Collision &collision, Block &collider) {
    bool intersect = false;
    Cylinder shape;
    shape.physical().position(collider.physical().position());
    shape.physical().velocity(collider.physical().velocity());
    shape.radius(0.5 * sqrt(collider.width() * collider.width() + collider.height() * collider.height()));
    if (cylinder(collision, shape)) {
        collision.collider(&collider);
        intersect = true;
    }
    return intersect;
}

//------------------------------------------------------------------------------
// cylinder collision with block
bool Block::cylinder(Collision &collision, Cylinder &collider) {
    bool intersect = false;
    if (collider.block(collision, *this)) {
        collision.collider(&collider);
        collision.obstacle(this);
        collision.normal(-collision.normal());
        intersect = true;
    }
    return intersect;
}

//------------------------------------------------------------------------------
// block mass
double Block::mass() const {
    return _physical.density() * width() * height() * depth();
}

//------------------------------------------------------------------------------
// block inertia
double Block::inertia() const {
    return mass() * (width() * width() + height() * height()) / 12.0;
}

//------------------------------------------------------------------------------
