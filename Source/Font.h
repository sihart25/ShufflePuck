//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Font.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Font_h
#define Font_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int CHARACTERS = 256;

    //------------------------------------------------------------------------------
    // class definition

    class Font {

    public:

        Font() : 
            _characters(0), 
            _italics(false), 
            _left(0.0), 
            _bottom(0.0), 
            _width(1.0), 
            _height(1.0) {}
        ~Font() {
            glDeleteLists(_characters, CHARACTERS);
        }
        void init();
        void set(const string &message, bool italics, double left, double bottom, double width, double height);
        void render(Game &/*game*/) const;

    private:

        Font(const Font &font);
        Font &operator=(const Font &font);

        GLuint _characters;
        string _message;
        bool _italics;
        double _left;
        double _bottom;
        double _width;
        double _height;

    };


} // ComputerGraphics

#endif // Font_h

//------------------------------------------------------------------------------
