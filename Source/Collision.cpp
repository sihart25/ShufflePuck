//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Collision.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#pragma hdrstop
#include "Collision.h"
#include "Vectors.h"
#include "Constants.h"
#include "Game.h"
#include "Label.h"
#include "Shape.h"
#include "Block.h"
#include "Cylinder.h"
#include "Sound.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// colliders container
void Collision::colliders(const Game &game) {
    Label *scene = (Label *)(game.find("Scene"));
    _colliders.clear();
    scene->colliders(game, _colliders);
}

//------------------------------------------------------------------------------
// obstacles container
void Collision::obstacles(const Game &game) {
    Label *scene = (Label *)(game.find("Scene"));
    _obstacles.clear();
    scene->obstacles(game, _obstacles);
}

//------------------------------------------------------------------------------
// collision update
void Collision::update(const Game &game, double rate) {
    const int ITERATIONS = 10;
    int steps = 0;
    if (fabs(rate) >= EPSILON) {
        steps = (int)((double)RESOLUTION / rate);
    }
    if (steps > RESOLUTION) {
        steps = RESOLUTION;
    }
    Label *scene = (Label *)(game.find("Scene"));
    for (int step = 0; step < steps; step++) {
        double timeRemaining = 1.0 / (double)RESOLUTION;
        for (int iteration = 0; iteration < ITERATIONS; iteration++) {
            _collision = false;
            _time = timeRemaining;
            _collider = 0;
            _obstacle = 0;
            collision(game);
            if (_collision) {
                if (_time > EPSILON) {
                    scene->update(game, _time - EPSILON);
                }
                response(game);
            }
            else {
                scene->update(game, timeRemaining);
                break;
            }
            timeRemaining -= _time;
        }
        if (iteration == ITERATIONS) {
            cout << "!";
        }
    }
}

//------------------------------------------------------------------------------
// collision detection
void Collision::collision(const Game &game) {
    vector<Shape *>::const_iterator collider;
    vector<Shape *>::const_iterator obstacle;
    for (collider = _colliders.begin(); collider != _colliders.end(); collider++) {
        for (obstacle = collider + 1; obstacle != _colliders.end(); obstacle++) {
            (*collider)->collision(*this, **obstacle);
        }
        for (obstacle = _obstacles.begin(); obstacle != _obstacles.end(); obstacle++) {
            if (!((*collider)->puck() && (*obstacle)->line())) {
                (*collider)->collision(*this, **obstacle);
            }
        }
    }
}

//------------------------------------------------------------------------------
// collision response
void Collision::response(const Game &game) {
    // largest restitution
    double restitution;
    if (_collider->physical().restitution() >= _obstacle->physical().restitution()) {
        restitution = _collider->physical().restitution();
    }
    else {
        restitution = _obstacle->physical().restitution();
    }
    // largest friction
    double friction;
    if (_collider->physical().friction() >= _obstacle->physical().friction()) {
        friction = _collider->physical().friction();
    }
    else {
        friction = _obstacle->physical().friction();
    }
    Vectors up = Vectors(0.0, 0.0, 1.0, 0.0);
    Vectors tangent = up.cross(_normal);
    if (_obstacle->player() || _obstacle->puck()) {
        // moving obstacle
        double totalMass = _collider->mass() + _obstacle->mass();
        Vectors colliderPerpendicular = _collider->physical().velocity().dot(_normal) * _normal;
        Vectors obstaclePerpendicular = _obstacle->physical().velocity().dot(_normal) * _normal;
        Vectors colliderParallel = _collider->physical().velocity() - colliderPerpendicular;
        Vectors obstacleParallel = _obstacle->physical().velocity() - obstaclePerpendicular;
        // velocity
        Vectors colliderParallelSpin = colliderParallel - _collider->physical().spin() * DEG_TO_RAD *
            (_collider->physical().position() - _position).magnitude() * tangent;
        Vectors obstacleParallelSpin = obstacleParallel + _obstacle->physical().spin() * DEG_TO_RAD *
            (_obstacle->physical().position() - _position).magnitude() * tangent;
        Vectors parallelMomentum = _collider->mass() * colliderParallel + _obstacle->mass() * obstacleParallel;
        Vectors parallelVelocityAfter = (colliderParallel - obstacleParallel) - friction * (colliderParallelSpin - obstacleParallelSpin);
        Vectors perpendicularMomentum = _collider->mass() * colliderPerpendicular + _obstacle->mass() * obstaclePerpendicular;
        Vectors perpendicularVelocityAfter = restitution * (colliderPerpendicular - obstaclePerpendicular);
        Vectors colliderPerpendicularAfter = (perpendicularMomentum - _obstacle->mass() * perpendicularVelocityAfter) / totalMass;
        Vectors obstaclePerpendicularAfter = (perpendicularMomentum + _collider->mass() * perpendicularVelocityAfter) / totalMass;
        Vectors colliderParallelAfter = (parallelMomentum + _obstacle->mass() * parallelVelocityAfter) / totalMass;
        Vectors obstacleParallelAfter = (parallelMomentum - _collider->mass() * parallelVelocityAfter) / totalMass;
        _collider->physical().velocity(colliderPerpendicularAfter + colliderParallelAfter);
        _obstacle->physical().velocity(obstaclePerpendicularAfter + obstacleParallelAfter);
        // spin
        Vectors colliderParallelChange = colliderParallelAfter - colliderParallel;
        double colliderSpinChange = _collider->mass() * colliderParallelChange.magnitude() *
            fabs(_normal.dot(_collider->physical().position() - _position)) / _collider->inertia() * RAD_TO_DEG;
        if (_normal.cross(colliderParallelChange).z() >= 0.0) {
            _collider->physical().spin(_collider->physical().spin() - colliderSpinChange);
        }
        else {
            _collider->physical().spin(_collider->physical().spin() + colliderSpinChange);
        }
        Vectors obstacleParallelChange = obstacleParallelAfter - obstacleParallel;
        double obstacleSpinChange = _obstacle->mass() * obstacleParallelChange.magnitude() * 
            fabs(_normal.dot(_obstacle->physical().position() - _position)) / _obstacle->inertia() * RAD_TO_DEG;
        if (_normal.cross(obstacleParallelChange).z() >= 0.0) {
            _obstacle->physical().spin(_obstacle->physical().spin() + obstacleSpinChange);
        }
        else {
            _obstacle->physical().spin(_obstacle->physical().spin() - obstacleSpinChange);
        }
    }
    else {
        // fixed obstacle
        Vectors perpendicular = _collider->physical().velocity().dot(_normal) * _normal;
        Vectors parallel = _collider->physical().velocity() - perpendicular;
        if (!_collider->player()) {
            // velocity
            Vectors parallelSpin = parallel - _collider->physical().spin() * DEG_TO_RAD *
                (_collider->physical().position() - _position).magnitude() * tangent;
            Vectors parallelAfter = parallel - friction * parallelSpin;
            Vectors perpendicularAfter = -restitution * perpendicular;
            _collider->physical().velocity(perpendicularAfter + parallelAfter);
            // spin
            Vectors parallelChange = parallelAfter - parallel;
            double spinChange = _collider->mass() * parallelChange.magnitude() *
                fabs(_normal.dot(_collider->physical().position() - _position)) / _collider->inertia() * RAD_TO_DEG;
            if (_normal.cross(parallelChange).z() >= 0.0) {
                _collider->physical().spin(_collider->physical().spin() - spinChange);
            }
            else {
                _collider->physical().spin(_collider->physical().spin() + spinChange);
            }
        }
        else {
            _collider->physical().velocity(-restitution * perpendicular + (1.0 - friction) * parallel);
        }
    }
    if (_collider->puck() || _obstacle->puck()) {
        double colliderVolume = _collider->physical().velocity().magnitude() / 20.0;
        double obstacleVolume = _obstacle->physical().velocity().magnitude() / 20.0;
        if (colliderVolume >= obstacleVolume) {
            ((Sound *)(game.find("Woosh")->nodes()[0]))->volume(colliderVolume);
        }
        else {
            ((Sound *)(game.find("Woosh")->nodes()[0]))->volume(obstacleVolume);
        }
        game.find("Woosh")->render(game);
    }
}

//------------------------------------------------------------------------------
