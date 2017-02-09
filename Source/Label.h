//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Label.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Label_h
#define Label_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Group.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Label : public Group {

    public:

        Label() : Group(),
            _draw(false), 
            _stencil(false), 
            _object(true), 
            _reflect(true), 
            _floor(false), 
            _shadow(true), 
            _displayList(false), 
            _list(0),
            _number(1) {}
        ~Label() {
            erase();
        }
        virtual Node *clone() const { return new Label(*this); }
        static void read(istream &in, string &token, Game &game);
        virtual void render(const Game &game) const;

        void draw(const Game &game) const;
        void stencil(const Game &game) const;
        void object(const Game &game) const;
        void reflect(const Game &game) const;
        void floor(const Game &game) const;
        void shadow(const Game &game) const;
        void draw(bool draw) { _draw = draw; }
        void stencil(bool stencil) { _stencil = stencil; }
        void object(bool object) { _object = object; }
        void reflect(bool reflect) { _reflect = reflect; }
        void floor(bool floor) { _floor = floor; }
        void shadow(bool shadow) { _shadow = shadow; }
        int number() const { return _number; }

    private:

        void erase() {
            if (_displayList) {
                glDeleteLists(_list, 1);
            }
        }
        virtual void write(ostream &out) const { cout << "Label"; }

        bool _draw;
        bool _stencil;
        bool _object;
        bool _reflect;
        bool _floor;
        bool _shadow;
        bool _displayList;
        GLuint _list;
        int _number;

    };

} // ComputerGraphics

#endif // Label_h

//------------------------------------------------------------------------------
