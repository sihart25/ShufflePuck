//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Camera.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Camera_h
#define Camera_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Node.h"
#include "Group.h"
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

    class Camera : public Node {

    public:

        Camera() :
            _position(0.0, 0.0, 0.0, 1.0), 
            _direction(0.0, 0.0, -1.0, 0.0), 
            _up(0.0, 1.0, 0.0, 0.0), 
            _fieldOfView(60.0) {}
        virtual Node *clone() const { return new Camera(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void render(const Game &game) const;

        void position(const Vectors &position) { _position = position; }
        void direction(const Vectors &direction) { _direction = direction; }
        void up(const Vectors &up) { _up = up; }
        void fieldOfView(double fieldOfView) { _fieldOfView = fieldOfView; }
        const Vectors &position() { return _position; }
        const Vectors &direction() { return _direction; }
        const Vectors &up() { return _up; }
        double fieldOfView() { return _fieldOfView; }

    private:

        virtual void write(ostream &out) const { out << "Camera" << endl; }

        Vectors _position;
        Vectors _direction;
        Vectors _up;
        double _fieldOfView;

    };

} // ComputerGraphics

#endif // Camera_h

//------------------------------------------------------------------------------
