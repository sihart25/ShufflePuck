//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Reference.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Reference_h
#define Reference_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Group.h"
#include "Game.h"
#include "Shape.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Reference : public Node {

    public:

        Reference(const string &label = "") :
            _label(label),
            _index(0) {}
        virtual Node *clone() const { return new Reference(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void read(istream &in, string &token);
        virtual void colliders(const Game &game, vector<Shape *> &colliders);
        virtual void obstacles(const Game &game, vector<Shape *> &obstacles);
        virtual void update(const Game &game, double time);
        virtual void render(const Game &game) const;

    private:

        virtual void write(ostream &out) const { cout << "Reference" << endl; }

        string _label;
        int _index;

    };

} // ComputerGraphics

#endif // Reference_h

//------------------------------------------------------------------------------
