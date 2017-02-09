//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Group.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Group_h
#define Group_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Light;
    class Shape;

    //------------------------------------------------------------------------------
    // class definition

    class Group : public Node {

    public:

        Group() :
            _owner(true) {}
        Group(const Group &group) {
            copy(group);
        }
        Group &operator=(const Group &group) {
            if (this != &group) {
                erase();
                copy(group);
            }
            return *this;
        }
        virtual ~Group() {
            erase();
        }
        virtual Node *clone() const { return new Group(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void colliders(const Game &game, vector<Shape *> &colliders);
        virtual void obstacles(const Game &game, vector<Shape *> &obstacles);
        virtual void update(const Game &game, double time);
        virtual void render(const Game &game) const;

        void push_back(Node *node) { _nodes.push_back(node); }
        void pop_back() { _nodes.pop_back(); }
        Node *back() { return _nodes.back(); }
        const vector<Node *> &nodes() const { return _nodes; }

    private:

        void erase();
        void copy(const Group &group);
        virtual void write(ostream &out) const { cout << "Group"; }

    protected:

        vector<Node *> _nodes;
        bool _owner;

    };

} // ComputerGraphics

#endif // Group_h

//------------------------------------------------------------------------------
