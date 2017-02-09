//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Sound.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#ifdef _OPENAL
#include <AL/alut.h>
#endif
#pragma hdrstop
#include "Sound.h"
#include "Group.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
bool Sound::_enable = true;

//------------------------------------------------------------------------------
// init sound
void Sound::init(int *argc, char **argv) {
    #ifdef _OPENAL
	alutInit(argc, argv);
    float position[3] = { 0.0, 0.0, 0.0 };
    float orientation[6] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
    alListenerfv(AL_POSITION, position);
    alListenerfv(AL_ORIENTATION, orientation);
    alListenerf(AL_GAIN, 1.0);
    #endif
}

//------------------------------------------------------------------------------
// close sound
void Sound::close() {
    #ifdef _OPENAL
	alutExit();
    #endif
}

//------------------------------------------------------------------------------
// read sound with static method
bool Sound::read(istream &in, string &token, Group &group) {
    if (token == "Sound") {
        in >> token;
        if (token != OPENING_BRACE) {
            throw string("Error : Missing sound opening brace");
        }
        in >> token;
        Sound *sound = new Sound;
        group.push_back(sound);
        while (token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {
            }
            else if (token == "Filename") {
                in >> sound->_filename >> token;
            }
            else {
                throw string("Error : Invalid sound attribute = " + token);
            }
        }
        in >> token;
        #ifdef _OPENAL
        alGenBuffers(1, &sound->_buffer);
        if (!alIsBuffer(sound->_buffer)) {
		    throw string("Error : Failed sound buffer creation");
	    }
	    ALenum format;
	    ALvoid *data;
	    ALsizei size;
        ALsizei freq;
        #ifdef WIN32
	    alutLoadWAVFile(const_cast<ALbyte *>(sound->_filename.c_str()), &format, &data, &size, &freq);
	    alBufferData(sound->_buffer, format, data, size, freq);
	    alutUnloadWAV(format, data, size, freq);
        #else
        ALsizei bits
	    alutLoadWAV(const_cast<ALbyte *>(sound->_filename.c_str()), &data, &format, &size, &bits, &freq);
	    alBufferData(sound->_buffer, format, data, size, freq);
	    free(data);
        #endif
        alGenSources(VOICES, sound->_sources);
        for (int voice = 0; voice < VOICES; voice++) {
            if (!alIsSource(sound->_sources[voice])) {
    		    throw string("Error : Failed sound source creation");
	        }
	        alSourcei(sound->_sources[voice], AL_BUFFER, sound->_buffer);
        }
        #endif
        return true;
    }
    else {
        return false;
    }
}

//------------------------------------------------------------------------------
// render sound
void Sound::render(const Game &/*game*/) const {
    #ifdef _OPENAL
    if (_enable) {
        float position[3] = { 0.0, 0.0, 0.0 };
        alSourcefv(_sources[_voice], AL_POSITION, position);
        alSourcef(_sources[_voice], AL_GAIN, _volume);
        alSourcePlay(_sources[_voice]);
        _voice = (_voice + 1) % VOICES;
    }
    #endif
}

//------------------------------------------------------------------------------
