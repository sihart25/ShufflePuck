//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Light.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Light_h
#define Light_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Node.h"
#include "Group.h"
#include "Colour.h"
#include "Vectors.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int GL_LIGHTS = 8;
    const GLenum GL_LIGHT[GL_LIGHTS] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
                                        GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

    //------------------------------------------------------------------------------
    // class definition

    class Light : public Node {

    public:

        Light() :
            _position(0.0, 0.0, 0.0, 1.0),
            _ambient(0.0, 0.0, 0.0, 1.0),
            _diffuse(0.0, 0.0, 0.0, 1.0),
            _specular(0.0, 0.0, 0.0, 1.0),
            _infinite(false) {}
        virtual Node *clone() const { return new Light(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void render(const Game &game) const;

        const Colour &ambient() const { return _ambient; }
        const Colour &diffuse() const { return _diffuse; }
        const Colour &specular() const { return _specular; }
        const Vectors &position() const { return _position; }
        bool infinite() const { return _infinite; }
        static int &count() { return _count; }

    private:

        virtual void write(ostream &out) const { cout << "Light"; }

        Colour _ambient;
        Colour _diffuse;
        Colour _specular;
        Vectors _position;
        bool _infinite;
        static int _count;

    };

} // ComputerGraphics

#endif // Light_h

//------------------------------------------------------------------------------
