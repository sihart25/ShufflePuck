//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Shape.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Shape_h
#define Shape_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Node.h"
#include "Material.h"
#include "Physical.h"
#include "Group.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Collision;
    class Block;
    class Cylinder;

    //------------------------------------------------------------------------------
    // class definition

    class Shape : public Node {

    public:

        Shape() :
            _player(false),
            _puck(false),
            _line(false),
            _obstacle(false) {}
        Shape(const Material &material, const Physical &physical) :
            _material(material),
            _physical(physical) {}
        virtual ~Shape() {}
        virtual Node *clone() const { return new Shape(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token) {}
        virtual void colliders(const Game &game, vector<Shape *> &colliders) {}
        virtual void obstacles(const Game &game, vector<Shape *> &obstacles) {}
        virtual void update(const Game &game, double time) { _physical.update(game, time); }
        virtual void render(const Game &game) const {}
        virtual bool collision(Collision &collision, Shape &obstacle) { return false; }
        virtual bool block(Collision &collision, Block &collider) { return false; }
        virtual bool cylinder(Collision &collision, Cylinder &collider) { return false; }
        virtual double mass() const { return 0.0; }
        virtual double inertia() const { return 0.0; }

        Material &material() { return _material; }
        Physical &physical() { return _physical; }
        bool player() const { return _player; }
        bool puck() const { return _puck; }
        bool line() const { return _line; }
        bool obstacle() const { return _obstacle; }

    protected:

        virtual void write(ostream &out) const { cout << "Shape" << endl; }

        Material _material;
        Physical _physical;
        bool _player;
        bool _puck;
        bool _line;
        bool _obstacle;

    };

} // ComputerGraphics

#endif // Shape_h

//------------------------------------------------------------------------------
