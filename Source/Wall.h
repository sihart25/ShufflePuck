//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShuffleWall Assessment
// Wall.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Wall_h
#define Wall_h

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

    class Wall : public Block {

    public:

        Wall() {
          _obstacle = true;
        }
        virtual Node *clone() const { return new Wall(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void obstacles(const Game &game, vector<Shape *> &obstacles);

    private:

        virtual void write(ostream &out) const { cout << "Wall" << endl; Block::write(out); }

    };

} // ComputerGraphics

#endif // Wall_h

//------------------------------------------------------------------------------
