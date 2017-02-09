//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Block.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Block_h
#define Block_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Node.h"
#include "Group.h"
#include "Game.h"
#include "Cylinder.h"

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

    class Block : public Shape {

    public:

        Block() :
            _width(1.0),
            _height(1.0),
            _depth(1.0),
            _left(0.0), 
            _right(1.0),
            _bottom(0.0),
            _top(1.0) {}
        virtual Node *clone() const { return new Block(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void render(const Game &game) const;
        virtual bool collision(Collision &collision, Shape &obstacle) {
            return obstacle.block(collision, *this);
        }
        virtual bool block(Collision &collision, Block &collider);
        virtual bool cylinder(Collision &collision, Cylinder &collider);
        virtual double mass() const;
        virtual double inertia() const;

        void width(double width) { _width = width; }
        void height(double height) { _height = height; }
        void depth(double depth) { _depth = depth; }
        double width() const { return _width; }
        double height() const { return _height; }
        double depth() const { return _depth; }

    protected:

        virtual void write(ostream &out) const { cout << "Block" << endl; Shape::write(out); }

        double _width;
        double _height;
        double _depth;
        double _left;
        double _right;
        double _bottom;
        double _top;

    };

} // ComputerGraphics

#endif // Block_h

//------------------------------------------------------------------------------
