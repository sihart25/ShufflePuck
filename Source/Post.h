//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePost Assessment
// Post.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Post_h
#define Post_h

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

    class Post : public Cylinder {

    public:

        Post() {
          _obstacle = true;
        }
        virtual Node *clone() const { return new Post(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void obstacles(const Game &game, vector<Shape *> &obstacles);

    private:

        virtual void write(ostream &out) const { cout << "Post" << endl; Cylinder::write(out); }

    };

} // ComputerGraphics

#endif // Post_h

//------------------------------------------------------------------------------
