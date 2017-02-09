//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Label.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <GL/glut.h>
#pragma hdrstop
#include "Label.h"
#include "Node.h"
#include "Group.h"
#include "Reader.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read label
void Label::read(istream &in, string &token, Game &game) {
    string key;
    Label *label;
    while (!in.eof()) {
        if (Reader::comment(in, token)) {
        }
        else {
            key = token;
            in >> token;
            if (token != OPENING_BRACE) {
                throw string("Error : Missing label opening brace");
            }
            in >> token;
            label = new Label();
            while (token != CLOSING_BRACE) {
                if (token == "Draw") {
                    in >> label->_draw >> token;
                }
                else if (token == "Stencil") {
                    in >> label->_stencil >> token;
                }
                else if (token == "Object") {
                    in >> label->_object >> token;
                }
                else if (token == "Floor") {
                    in >> label->_floor >> token;
                }
                else if (token == "Reflect") {
                    in >> label->_reflect >> token;
                }
                else if (token == "Shadow") {
                    in >> label->_shadow >> token;
                }
                else if (token == "DisplayList") {
                    in >> label->_displayList >> token;
                }
                else if (token == "Number") {
                    in >> label->_number >> token;
                }
                else if (token == "Owner") {
                    in >> label->_owner >> token;
                }
                else if (Node::read(in, token, *label)) {
                }
                else {
                    throw string("Error : Invalid label attribute = " + token);
                }
            }
            in >> token;
            game.insert(key, label);
            if (label->_displayList) {
                label->_list = glGenLists(1);
                glNewList(label->_list, GL_COMPILE);
                label->draw(game);
                glEndList();
            }
            for (int i = 1; i < label->_number; i++) {
                Label *copy = new Label(*label);
                game.insert(key, copy);
            }
        }
    }
}

//------------------------------------------------------------------------------
// render label
void Label::render(const Game &game) const {
    if (_draw) {
        draw(game);
    }
    else {
        switch (game.phase()) {
            case Game::STENCILS: {
                if (_stencil) {
                    stencil(game);
                }
                break;
            }
            case Game::OBJECTS: {
                if (_object) {
                    object(game);
                }
                break;
            }
            case Game::REFLECTIONS: {
                if (_reflect) {
                    reflect(game);
                }
                break;
            }
            case Game::FLOORS: {
                if (_floor) {
                    floor(game);
                }
                break;
            }
            case Game::SHADOWS: {
                if (_shadow) {
                    shadow(game);
                }
                break;
            }
        }
    }
}

//------------------------------------------------------------------------------
// draw label
void Label::draw(const Game &game) const {
    for (vector<Node *>::const_iterator node = _nodes.begin(); node != _nodes.end(); node++) {
        (*node)->render(game);
    }
}

//------------------------------------------------------------------------------
// draw stencil
void Label::stencil(const Game &game) const {
    // set stencil to 1's when pre-rendering floor
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 255, 255);
    glStencilMask(255);
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);
    if (_displayList) {
        glCallList(_list);
    }
    else {
        draw(game);
    }
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glDisable(GL_STENCIL_TEST);
}

//------------------------------------------------------------------------------
// draw object
void Label::object(const Game &game) const {
    // set stencil to 0's when rendering objects
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 0, 255);
    glStencilMask(255);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    if (_displayList) {
        glCallList(_list);
    }
    else {
        draw(game);
    }
    glDisable(GL_STENCIL_TEST);
}

//------------------------------------------------------------------------------
// draw reflect
void Label::reflect(const Game &game) const {
    glPushMatrix();
    glScaled(1.0, 1.0, -1.0);
    glCullFace(GL_FRONT);
    // test stencil bit 0 for 1 when rendering reflections
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilMask(1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    if (_displayList) {
        glCallList(_list);
    }
    else {
        draw(game);
    }
    glDisable(GL_STENCIL_TEST);
    glCullFace(GL_BACK);
    glPopMatrix();
}

//------------------------------------------------------------------------------
// draw floor
void Label::floor(const Game &game) const {
    // render the floor with transparency to simulate reflections but without writing depth
    glDepthMask(GL_FALSE);
    if (_displayList) {
        glCallList(_list);
    }
    else {
        draw(game);
    }
    glDepthMask(GL_TRUE);
}

//------------------------------------------------------------------------------
// draw shadow
void Label::shadow(const Game &game) const {
    // render the shadows with transparency to simulate shadows but without writing depth
    Vectors light;
    int mask = 0;
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        switch (i) {
            case 0: {
                light = Vectors(-10.0, -5.0, 4.0, 1.0);
                mask = 2;
                break;
            }
            case 1: {
                light = Vectors(10.0, -5.0, 4.0, 1.0);
                mask = 4;
                break;
            }
            case 2: {
                light = Vectors(10.0, 5.0, 4.0, 1.0);
                mask = 8;
                break;
            }
            case 3: {
                light = Vectors(-10.0, 5.0, 4.0, 1.0);
                mask = 16;
                break;
            }
        }
        Vectors plane(0.0, 0.0, 0.0, 1.0);
        Vectors normal(0.0, 0.0, 1.0, 0.0);
        double normalDotLight = normal.dot(light);
        double normalDotPlane = normal.dot(plane);
        double normalDotPlaneMinusLight = normal.dot(plane - light);
        double matrix[4][4];
        // first row
        matrix[0][0] = -light.x() * normal.x() - normalDotPlaneMinusLight;
        matrix[1][0] = -light.x() * normal.y();
        matrix[2][0] = -light.x() * normal.z();
        matrix[3][0] = normalDotPlane * light.x();
        // second row
        matrix[0][1] = -light.y() * normal.x();
        matrix[1][1] = -light.y() * normal.y() - normalDotPlaneMinusLight;
        matrix[2][1] = -light.y() * normal.z();
        matrix[3][1] = normalDotPlane * light.y();
        // third row
        matrix[0][2] = -light.z() * normal.x();
        matrix[1][2] = -light.z() * normal.y();
        matrix[2][2] = -light.z() * normal.z() - normalDotPlaneMinusLight;
        matrix[3][2] = normalDotPlane * light.z();
        // fourth row
        matrix[0][3] = -normal.x();
        matrix[1][3] = -normal.y();
        matrix[2][3] = -normal.z();
        matrix[3][3] = normalDotLight;
        glMultMatrixd(&matrix[0][0]);
        // set stencil bit n for 1 when rendering shadows
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 0, mask);
        glStencilMask(mask);
        glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
        glDisable(GL_LIGHTING);
        glColor4f(0.0, 0.0, 0.0, 0.1);
        glDepthMask(GL_FALSE);
        if (_displayList) {
            glCallList(_list);
        }
        else {
            draw(game);
        }
        glDepthMask(GL_TRUE);
        glEnable(GL_LIGHTING);
        glDisable(GL_STENCIL_TEST);
        glPopMatrix();
    }
}

//------------------------------------------------------------------------------
