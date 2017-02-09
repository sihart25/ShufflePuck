//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Physical.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Physical_h
#define Physical_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Vectors.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Physical {

    public:

        Physical() :
            _position(0.0, 0.0, 0.0, 1.0),
            _velocity(0.0, 0.0, 0.0, 0.0),
            _axis(0.0, 0.0, 1.0, 0.0),
            _angle(0.0),
            _spin(0.0),
            _density(1.0),
            _restitution(0.0),
            _friction(0.0),
            _damping(0.0) {}
        bool read(istream &in, string &token);
        void update(const Game &game, double time);
        void render(const Game &game) const;

        void position(const Vectors &position) { _position = position; }
        void velocity(const Vectors &velocity) { _velocity = velocity; }
        void axis(const Vectors &axis) { _axis = axis; }
        void angle(double angle) { _angle = angle; }
        void spin(double spin) { _spin = spin; }
        const Vectors &position() const { return _position; }
        const Vectors &velocity() const { return _velocity; }
        const Vectors &axis() const { return _axis; }
        double angle() const { return _angle; }
        double spin() const { return _spin; }

        double density() const { return _density; }
        double restitution() const { return _restitution; }
        double friction() const { return _friction; }
        double damping() const { return _damping; }

    private:

        Vectors _position;
        Vectors _velocity;
        Vectors _axis;
        double _angle;
        double _spin;
        double _density;
        double _restitution;
        double _friction;
        double _damping;

    };

} // ComputerGraphics

#endif // Physical_h

//------------------------------------------------------------------------------
