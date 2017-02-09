//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Transform.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Transform_h
#define Transform_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Node.h"
#include "Group.h"
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

    class Transform : public Node {

    public:

        Transform() :
            _translate(0.0, 0.0, 0.0, 0.0),
            _axis(0.0, 0.0, 1.0, 0.0),
            _angle(0.0),
            _scale(1.0, 1.0, 1.0) {}
        virtual Node *clone() const { return new Transform(*this); }
        static bool read(istream &in, string &token, Group &group);
        void read(istream &in, string &token);
        virtual void render(const Game &game) const;

        void translate(const Vectors &translate) { _translate = translate; }
        void axis(const Vectors &axis) { _axis = axis; }
        void angle(double angle) { _angle = angle; }
        void scale(const Vectors &scale) { _scale = scale; }
        const Vectors &translate() const { return _translate; }
        const Vectors &axis() const { return _axis; }
        double angle() const { return _angle; }
        const Vectors &scale() const {  return _scale; }

    private:

        virtual void write(ostream &out) const { out << "Transform" << endl; }

        Vectors _translate;
        Vectors _axis;
        double _angle;
        Vectors _scale;

    };

} // ComputerGraphics

#endif // Transform_h

//------------------------------------------------------------------------------
