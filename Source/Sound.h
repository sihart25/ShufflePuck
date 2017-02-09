//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Sound.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Sound_h
#define Sound_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#ifdef _OPENAL
#include <AL/alut.h>
#endif
#include "Node.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int VOICES = 5;

    //------------------------------------------------------------------------------
    // class definition

    class Sound : public Node {

    public:

        Sound() :
            _volume(1.0) {
            #ifdef _OPENAL
            _voice = 0;
            _buffer = 0;
            for (int voice = 0; voice < VOICES; voice++) {
                _sources[voice] = 0;
            }
            #endif
        }
        ~Sound() {
            #ifdef _OPENAL
            alDeleteSources(VOICES, _sources);
            alDeleteBuffers(1, &_buffer);
            #endif
        }
        virtual Node *clone() const { return 0; }
        static void init(int *argc, char **argv);
        static void close();
        static bool read(istream &in, string &token, Group &group);
        virtual void render(const Game &game) const;

        static void enable(bool enable) { _enable = enable; }
        static bool enable() { return _enable; }
        void volume(double volume) { _volume = (volume < 1.0) ? volume : 1.0; }

    private:

        Sound(const Sound &sound);
        Sound &operator=(const Sound &sound);
        virtual void write(ostream &out) const { cout << "Sound" << endl; }

        static bool _enable;
        string _filename;
        double _volume;
        #ifdef _OPENAL
        mutable int _voice;
        ALuint _buffer;
        ALuint _sources[VOICES];
        #endif

    };

} // ComputerGraphics

#endif // Sound_h

//------------------------------------------------------------------------------
