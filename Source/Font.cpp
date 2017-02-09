//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Font.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Font.h"
#include "Game.h"
#include "Label.h"
#include "Material.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// init
void Font::init() {
    const int COLUMNS = 16;
    const int ROWS = 16;
    const double WIDTH = 1.0 / (double)COLUMNS;
    const double HEIGHT = 1.0 / (double)ROWS;
    const double SPACING = 1.0;
    _characters = glGenLists(CHARACTERS);
    for (int character = 0; character < CHARACTERS; character++) {
        double left = double(character % COLUMNS) * WIDTH;
        double right = left + WIDTH;
        double bottom = double(ROWS - 1 - character / COLUMNS) * HEIGHT;
        double top = bottom + HEIGHT;
        glNewList(_characters + character, GL_COMPILE);
        glBegin(GL_QUADS);
        glTexCoord2d(left, bottom);
        glVertex3d(0.0, 0.0, 0.0);
        glTexCoord2d(right, bottom);
        glVertex3d(1.0, 0.0, 0.0);
        glTexCoord2d(right, top);
        glVertex3d(1.0, 1.0, 0.0);
        glTexCoord2d(left, top);
        glVertex3d(0.0, 1.0, 0.0);
        glEnd();
        glTranslated(SPACING, 0.0, 0.0);
        glEndList();
    }
}

//------------------------------------------------------------------------------
// set
void Font::set(const string &message, bool italics, double left, double bottom, double width, double height) {
    _message = message;
    _italics = italics;
    _left = left;
    _bottom = bottom;
    _width = width;
    _height = height;
}

//------------------------------------------------------------------------------
// render
void Font::render(Game &game) const {
    const double BORDER = 0.25;
    string key("AerialCamera");
    game.key(key);
    game.find(key)->render(game);
    glTranslated(_left, _bottom, 0.0);
    glScaled(_width, _height, 1.0);
    glTranslated(-0.5 * (double)(_message.length()), 0.0, 0.0);
    glDisable(GL_DEPTH_TEST);
    Material border;
    border.emission(Colour(1.0, 0.0, 0.0));
    border.render(game);
    glBegin(GL_QUADS);
    glVertex3d(-BORDER, -BORDER, 0.0);
    glVertex3d((double)(_message.length()) + BORDER, -BORDER, 0.0);
    glVertex3d((double)(_message.length()) + BORDER, 1.0 + BORDER, 0.0);
    glVertex3d(-BORDER, 1.0 + BORDER, 0.0);
    glEnd();
    game.find("Font")->render(game);
    Material material;
    material.texture(true);
    material.render(game);
    glListBase(_characters + (_italics ? 128 : 0) - 32);
    glCallLists(_message.length(), GL_BYTE, _message.c_str());
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

//------------------------------------------------------------------------------
