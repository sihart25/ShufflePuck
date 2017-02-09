//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Puck.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Puck_h
#define Puck_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Cylinder.h"
#include "Group.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Puck : public Cylinder {

    public:

        Puck() :
            _live(false) {
            _puck = true;
        }
        virtual Node *clone() const { return new Puck(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void colliders(const Game &game, vector<Shape *> &colliders);

        bool live() const { return _live; }
        void live(bool live) { _live = live; }

    private:

        virtual void write(ostream &out) const { cout << "Puck" << endl; Cylinder::write(out); }

        bool _live;

    };

} // ComputerGraphics

#endif // Puck_h

//------------------------------------------------------------------------------
