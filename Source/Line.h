//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShuffleLine Assessment
// Line.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Line_h
#define Line_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Block.h"
#include "Group.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Line : public Block {

    public:

        Line() {
            _line = true;
        }
        virtual Node *clone() const { return new Line(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void obstacles(const Game &game, vector<Shape *> &obstacles);

    private:

        virtual void write(ostream &out) const { cout << "Line" << endl; Block::write(out); }

    };

} // ComputerGraphics

#endif // Line_h

//------------------------------------------------------------------------------
