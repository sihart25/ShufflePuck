//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Screen.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Screen_h
#define Screen_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Node.h"
#include "Group.h"
#include "Colour.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Screen : public Node {

    public:

        virtual Node *clone() const { return new Screen(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void render(const Game &game) const;

    private:

        virtual void write(ostream &out) const { cout << "Screen" << endl; }

        Colour _background;

    };

} // ComputerGraphics

#endif // Screen_h

//------------------------------------------------------------------------------
