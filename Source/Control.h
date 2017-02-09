//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Control.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Control_h
#define Control_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <ctime>
#include "Game.h"
#include "Font.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Control {

    public:

        enum View {
            NONE,
            PLAYER,
            AERIAL,
            PUCK,
            CROSS,
            STEREO,
            LEFT,
            RIGHT
        };

        Control() :
            _view(PLAYER),
            _inset(NONE),
            _score(true),
            _reflections(true),
            _shadows(true),
            _fog(true),
            _wireframe(false),
            _motionX(0),
            _motionY(0),
            _count(0),
            _rate(0.0) {
            _then = clock();
        }
        ~Control() { cout << "Control node destructed" << endl; }
        void initialize(int *argc, char **argv);
        void menu() const;
        void display();
        void reshape(int width, int height);
        void keyboard(unsigned char key, int x, int y);
        void special(int key, int x, int y);
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);
        void idle();

    private:

        void start();

        string _filename;
        Font _font;
        Game _game;
        View _view;
        View _inset;
        bool _score;
        bool _reflections;
        bool _shadows;
        bool _fog;
        bool _wireframe;
        int _motionX;
        int _motionY;
        int _count;
        double _rate;
        clock_t _then;

    };

} // ComputerGraphics

#endif // Control_h

//------------------------------------------------------------------------------
