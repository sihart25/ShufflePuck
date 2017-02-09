//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Material.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Material.h"
#include "Colour.h"
#include "Reader.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read material
bool Material::read(istream &in, string &token) {
    if (token == "Material") {
        in >> token;
        if (token != "{") {
            throw string("Error : Missing material open brace");
        }
        in >> token;
        while (token != "}") {
            if (Reader::comment(in, token)) {}
            else if (token == "Ambient") {
                in >> _ambient >> token;
            }
            else if (token == "Diffuse") {
                in >> _diffuse >> token;
            }
            else if (token == "Specular") {
                in >> _specular >> token;
            }
            else if (token == "Shininess") {
                in >> _shininess >> token;
            }
            else if (token == "Emission") {
                in >> _emission >> token;
            }
            else if (token == "Alpha") {
                in >> _diffuse(A) >> token;
            }
            else if (token == "Texture") {
                in >> _texture >> token;
            }
            else {
                throw string("Error : Invalid material attribute = " + token);
            }
        }
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// render material
void Material::render(const Game &/*game*/) const {
    GLfloat colour[COLOURS];
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient.toGLfloat(colour));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse.toGLfloat(colour));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular.toGLfloat(colour));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, _emission.toGLfloat(colour));
    if (_texture) {
        glEnable(GL_TEXTURE_2D);
    }
    else {
        glDisable(GL_TEXTURE_2D);
    }
}

//------------------------------------------------------------------------------
