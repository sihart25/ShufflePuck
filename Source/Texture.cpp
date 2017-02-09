//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Texture.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Texture.h"
#include "Group.h"
#include "Reader.h"
#include "Bitmap.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read texture with static method
bool Texture::read(istream &in, string &token, Group &group) {
    if (token == "Texture") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing texture opening brace");
        }
        in >> token;
        Texture *texture = new Texture;
        group.push_back(texture);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {
            }
            if (token == "Filename") {
                in >> texture->_filename >> token;
            }
            else if (token == "Mipmap") {
                in >> texture->_mipmap >> token;
            }
            else if (token == "Replace") {
                in >> texture->_replace >> token;
            }
            else {
                throw string("Error : Invalid texture attribute = " + token);
            }
        }
        in >> token;
        glGenTextures(1, &texture->_texture);
        glBindTexture(GL_TEXTURE_2D, texture->_texture);
        if (!glIsTexture(texture->_texture)) {
		    throw string("Error : Failed texture creation");
	    }
        Bitmap bitmap;
        bitmap.read(const_cast<char *>(texture->_filename.c_str()));
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width(), bitmap.height(), 0, 
            GL_RGB, GL_UNSIGNED_BYTE, bitmap.image());
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bitmap.width(), bitmap.height(), 
            GL_RGB, GL_UNSIGNED_BYTE, bitmap.image());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (texture->_mipmap) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        return true;
    }
    else {
        return false;
    }
}

//------------------------------------------------------------------------------
// render texture
void Texture::render(const Game &/*game*/) const {
    glBindTexture(GL_TEXTURE_2D, _texture);
    if (_replace) {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }
    else {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
}

//------------------------------------------------------------------------------
