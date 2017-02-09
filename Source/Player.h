//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Player.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Player_h
#define Player_h

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

    class Player : public Block {

    public:

        Player() :
            _speed(0.0),
            _spin(0.0),
            _score(0) {
            _player = true;
        }
        virtual Node *clone() const { return new Player(*this); }
        static bool read(istream &in, string &token, Group &group);
        virtual void colliders(const Game &game, vector<Shape *> &colliders);

        double speed() const { return _speed; }
        void speed(double speed) { _speed = speed; }
        double spin() const { return _spin; }
        void spin(double spin) { _spin = spin; }
        int score() const { return _score; }
        void score(int score) { _score = score; }

    private:

        virtual void write(ostream &out) const { cout << "Player" << endl; Block::write(out); }

        double _speed;
        double _spin;
        int _score;

    };

} // ComputerGraphics

#endif // Player_h

//------------------------------------------------------------------------------
