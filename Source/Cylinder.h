//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Cylinder.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Cylinder_h
#define Cylinder_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Group.h"
#include "Vectors.h"
#include "Game.h"
#include "Block.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Collision;

    //------------------------------------------------------------------------------
    // class definition

    class Cylinder : public Shape {

    public:

        Cylinder() :
            _radius(1.0),
            _height(1.0),
            _top(true),
            _bottom(true),
            _rows(5),
            _columns(20) {}
        virtual Node *clone() const { return new Cylinder(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void render(const Game &game) const;
        virtual bool collision(Collision &collision, Shape &obstacle) {
            return obstacle.cylinder(collision, *this);
        }
        virtual bool block(Collision &collision, Block &collider);
        virtual bool cylinder(Collision &collision, Cylinder &collider);
        virtual double mass() const;
        virtual double inertia() const;

        void radius(double radius) { _radius = radius; }
        void height(double height) { _height = height; }
        double radius() const { return _radius; }
        double height() const { return _height; }

    protected:

        virtual void write(ostream &out) const { cout << "Cylinder" << endl; Shape::write(out); }

        double _radius;
        double _height;
        bool _top;
        bool _bottom;
        int _rows;
        int _columns;

    };

} // ComputerGraphics

#endif // Cylinder_h

//------------------------------------------------------------------------------
