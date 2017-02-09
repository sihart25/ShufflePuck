//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Disc.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Disc_h
#define Disc_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Material.h"
#include "Vectors.h"
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

    class Disc : public Shape {

    public:

        Disc() :
            _radius(1.0),
            _rows(5),
            _columns(20) {}
        Disc(const Material &material, const Physical &physical, double radius, int rows, int columns) :
            Shape(material, physical),
            _radius(radius),
            _rows(rows),
            _columns(columns) {}
        virtual Node *clone() const { return new Disc(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void render(const Game &game) const;

    protected:

        virtual void write(ostream &out) const { cout << "Disc" << endl; Shape::write(out); }

        double _radius;
        int _rows;
        int _columns;

    };

} // ComputerGraphics

#endif // Disc_h

//------------------------------------------------------------------------------
