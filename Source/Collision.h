//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Collision.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Collision_h
#define Collision_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Game.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Collision {

    public:

        Collision() : 
            _collision(false), 
            _time(0.0), 
            _collider(0), 
            _obstacle(0),
            _normal(1.0, 0.0, 0.0, 0.0),
            _position(0.0, 0.0, 0.0, 1.0) {}
        void colliders(const Game &game);
        void obstacles(const Game &game);
        void update(const Game &game, double rate);
        void collision(bool collision) { _collision = collision; }

        void time(double time) { _time = time; }
        void collider(Shape *collider) { _collider = collider; }
        void obstacle(Shape *obstacle) { _obstacle = obstacle; }
        void normal(Vectors &normal) { _normal = normal; }
        void position(Vectors &position) { _position = position; }
        double time() const { return _time; }
        Shape *collider() const { return _collider; }
        Shape *obstacle() const { return _obstacle; }
        const Vectors &normal() const { return _normal; }
        const Vectors &position() const { return _position; }

    private:

        void collision(const Game &game);
        void response(const Game &game);

        vector<Shape *> _colliders;
        vector<Shape *> _obstacles;
        bool _collision;
        double _time;
        Shape *_collider;
        Shape *_obstacle;
        Vectors _normal;
        Vectors _position;

    };


} // ComputerGraphics

#endif // Collision_h

//------------------------------------------------------------------------------
