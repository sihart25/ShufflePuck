//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Node.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Node_h
#define Node_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Group;
    class Game;
    class Shape;

    //------------------------------------------------------------------------------
    // class definition

    class Node {

    public:

        virtual ~Node() {}
        virtual Node *clone() const = 0;
        static bool read(istream &in, string &token, Group &group);
        virtual void colliders(const Game &game, vector<Shape *> &colliders) {}
        virtual void obstacles(const Game &game, vector<Shape *> &obstacles) {}
        virtual void update(const Game &game, double time) {}
        virtual void render(const Game &game) const = 0;
        friend ostream &operator<<(ostream &out, const Node &node) {
            node.write(out);
            return out;
        }

    protected:

        virtual void write(ostream &out) const { cout << "Node" << endl; }

    };

} // ComputerGraphics

#endif // Node_h

//------------------------------------------------------------------------------
