//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Game.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Game_h
#define Game_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <map>
#include "Vectors.h"
#include "Node.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Label;
    class Transform;
    class Shape;

    //------------------------------------------------------------------------------
    // class definition

    class Game {

    public:

        enum Phase {
            STENCILS,
            OBJECTS,
            REFLECTIONS,
            FLOORS,
            SHADOWS
        };

        Game() :
            _key(""), 
            _phase(OBJECTS), 
            _pucks(0),
            _puck(0),
            _players(0),
            _player(0) {}
        Game(const Game &game) {
            copy(game);
        }
        Game &operator=(const Game &game) {
            if (this != &game) {
                erase();
                copy(game);
            }
            return *this;
        }
        ~Game() {
            erase();
        }
        void read(const string &filename);
        void render(const string &key, bool reflections, bool shadows);
        void start();
        void play(double rate);
        void addPlayer();
        void movePlayer(double speed, double spin);
        void addPuck();
        void removePuck();
        void nextPuck();
        int score(int player) const;
        void insert(const string &key, Label *label);
        Label *find(const string &key, int index = 0) const;

        void key(const string &key) { _key = key; }
        void phase(Phase phase) { _phase = phase; }
        void player(int player) { _player = player; }
        const string &key() const { return _key; }
        Phase phase() const { return _phase; }
        int player() { return _player; }

    private:

        void erase();
        void copy(const Game &game);

        multimap<string, Label *> _labels;
        string _key;
        Phase _phase;
        int _pucks;
        int _puck;
        int _players;
        int _player;

    };

} // ComputerGraphics

#endif // Game_h

//------------------------------------------------------------------------------
