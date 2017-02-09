//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Plane.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Plane_h
#define Plane_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
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

    class Plane : public Shape {

    public:

        Plane() :
            _width(1.0),
            _height(1.0),
            _left(0.0),
            _right(1.0),
            _bottom(0.0),
            _top(1.0),
            _rows(1),
            _columns(1) {}
        virtual Node *clone() const { return new Plane(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void render(const Game &game) const;

    protected:

        virtual void write(ostream &out) const { cout << "Plane" << endl; Shape::write(out); }

        double _width;
        double _height;
        double _left;
        double _right;
        double _bottom;
        double _top;
        int _rows;
        int _columns;

    };

} // ComputerGraphics

#endif // Plane_h

//------------------------------------------------------------------------------
