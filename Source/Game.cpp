//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Game.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <map>
#include <cmath>
#include <ctime>
#pragma hdrstop
#include "Game.h"
#include "Label.h"
#include "Transform.h"
#include "Reference.h"
#include "Camera.h"
#include "Vectors.h"
#include "Constants.h"
#include "Group.h"
#include "Collision.h"
#include "Block.h"
#include "Cylinder.h"
#include "Reader.h"
#include "Light.h"
#include "Puck.h"
#include "Player.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// erase game
void Game::erase() {
    for (multimap<string, Label *>::iterator label = _labels.begin();
        label != _labels.end(); label++) {
        delete label->second;
    }
    _labels.clear();
}

//------------------------------------------------------------------------------
// copy game
void Game::copy(const Game &game) {
    _key = game._key;
    _phase = game._phase;
    _pucks = game._pucks;
    _puck = game._puck;
    _players = game._players;
    _player = game._player;
    for (multimap<string, Label *>::const_iterator label = game._labels.begin();
        label != game._labels.end(); label++) {
        insert(label->first, label->second);
    }
}

//------------------------------------------------------------------------------
// read game
void Game::read(const string &filename) {
    Reader::read(filename, *this);
}

//------------------------------------------------------------------------------
// render game
void Game::render(const string &key, bool reflections, bool shadows) {
    glEnable(GL_LIGHTING);
    for (int count = 0; count < GL_LIGHTS; ++count) {
        glDisable(GL_LIGHT[count]);
    }
    Light::count() = 0;
    _key = key;
    if (reflections || shadows) {
        phase(Game::STENCILS);
        find(key)->render(*this);
    }
    phase(Game::OBJECTS);
    find(key)->render(*this);
    if (reflections) {
        phase(Game::REFLECTIONS);
        find(key)->render(*this);
    }
    phase(Game::FLOORS);
    find(key)->render(*this);
    if (shadows) {
        phase(Game::SHADOWS);
        find(key)->render(*this);
    }
}

//------------------------------------------------------------------------------
// insert label
void Game::insert(const string &key, Label *label) {
    _labels.insert(make_pair<string, Label *>(key, label));
}

//------------------------------------------------------------------------------
// find label
Label *Game::find(const string &key, int index) const {
    multimap<string, Label *>::const_iterator label = _labels.lower_bound(key);
    for (int i = 0; i < index; i++) {
        label++;
    }
    return (Label *)(label->second);
}

//------------------------------------------------------------------------------
// start game
void Game::start() {
    Label *scene = (Label *)find("Scene");
    scene->push_back((Label *)find("Stadium"));
    addPlayer();
    addPlayer();
    addPuck();
}

//------------------------------------------------------------------------------
// play game
void Game::play(double rate) {
    // update players
    for (int playerIndex = 0; playerIndex < _players; playerIndex++) {
        Player *player = (Player *)(find("Player", playerIndex)->nodes()[1]);
        player->physical().velocity(player->physical().velocity() +
            player->speed() * Vectors(sin(player->physical().angle() * DEG_TO_RAD),
            -cos(player->physical().angle() * DEG_TO_RAD), 0.0, 0.0));
        player->physical().spin(player->physical().spin() + player->spin());
        player->speed(0.0);
        player->spin(0.0);
    }

    // update collisions
    Collision collision;
    collision.colliders(*this);
    collision.obstacles(*this);
    collision.update(*this, rate);

    // update player camera
    Camera *playerCamera = (Camera *)(find("PlayerCamera")->nodes()[0]);
    Player *player = (Player *)(find("Player", _player)->nodes()[1]);
    playerCamera->position(player->physical().position());
    playerCamera->direction(Vectors(sin(player->physical().angle() * DEG_TO_RAD),
        -cos(player->physical().angle() * DEG_TO_RAD), -0.05, 0.0));

    // update puck camera
    Camera *puckCamera = (Camera *)(find("PuckCamera")->nodes()[0]);
    Puck *puck = (Puck *)(find("Puck", _puck)->nodes()[1]);
    puckCamera->position(puck->physical().position() + Vectors(0.0, 0.0, 0.2, 0.0));
    if (puck->physical().velocity().magnitude() > EPSILON) {
        puckCamera->direction(puck->physical().velocity());
    }

    // update score
    for (int puckIndex = 0; puckIndex < _pucks; puckIndex++) {
        Puck *puck = (Puck *)(find("Puck", puckIndex)->nodes()[1]);
        if (puck->physical().position().x() < -10.2) {
            if (puck->live()) {
                if (_player == 0) {
                    find("Doh")->render(*this);
                }
                else {
                    find("Woohoo")->render(*this);
                }
                Player *player = (Player *)(find("Player", 1)->nodes()[1]);
                player->score(player->score() + 1);
                puck->live(false);
            }
        }
        else if (puck->physical().position().x() > 10.2) {
            if (puck->live()) {
                if (_player == 0) {
                    find("Woohoo")->render(*this);
                }
                else {
                    find("Doh")->render(*this);
                }
                Player *player = (Player *)(find("Player", 0)->nodes()[1]);
                player->score(player->score() + 1);
                puck->live(false);
            }
        }
        else {
            puck->live(true);
        }
    }
}

//------------------------------------------------------------------------------
// score
int Game::score(int player) const {
    Player *players = (Player *)(find("Player", player)->nodes()[1]);
    return players->score();
}

//------------------------------------------------------------------------------
// add player
void Game::addPlayer() {
    if (_players < ((Label *)find("Player"))->number()) {
        Label *scene = (Label *)find("Scene");
        Label *label = (Label *)find("Player", _players);
        scene->push_back(label);
        double position;
        double angle;
        if (_players % 2 == 0) {
            position = -9.5;
            angle = 90.0;
        }
        else {
            position = 9.5;
            angle = 270;
        }
        Cylinder *player = (Cylinder *)(label->nodes()[1]);
        player->physical().position(Vectors(position, 0.0, player->physical().position().z(), 1.0));
        player->physical().velocity(Vectors(0.0, 0.0, 0.0, 0.0));
        player->physical().angle(angle);
        player->physical().spin(0.0);
        _players++;
    }
}

//------------------------------------------------------------------------------
// move player
void Game::movePlayer(double speed, double spin) {
    Player *player = (Player *)(find("Player", _player)->nodes()[1]);
    player->speed(player->speed() + speed);
    player->spin(player->spin() + spin);
}

//------------------------------------------------------------------------------
// add puck
void Game::addPuck() {
    if (_pucks < ((Label *)find("Puck"))->number()) {
        Label *scene = (Label *)find("Scene");
        Label *label = (Label *)find("Puck", _pucks);
        Puck *puck = (Puck *)(label->nodes()[1]);
        scene->push_back(label);
        double position;
        if (_pucks % 2 == 0) {
            position = ((_pucks + 1) / 2) * (2.0 * puck->radius() + 0.1);
        }
        else {
            position = -((_pucks + 1) / 2) * (2.0 * puck->radius() + 0.1);
        }
        puck->physical().position(Vectors(position, 0.0, puck->physical().position().z(), 1.0));
        puck->physical().velocity(Vectors(0.0, 0.0, 0.0, 0.0));
        puck->physical().angle(0.0);
        puck->physical().spin(0.0);
        puck->live(true);
        _pucks++;
    }
}

//------------------------------------------------------------------------------
// remove puck
void Game::removePuck() {
    if (_pucks > 0) {
        Label *scene = (Label *)find("Scene");
        Label *label = (Label *)(scene->back());
        Puck *puck = (Puck *)(label->nodes()[1]);
        puck->live(false);
        scene->pop_back();
        _pucks--;
    }
    if (_pucks == 0) {
        addPuck();
    }
    if (_puck >= _pucks) {
        _puck = _pucks - 1;
    }
}

//------------------------------------------------------------------------------
// next puck
void Game::nextPuck() {
    _puck = (_puck + 1) % _pucks;
}

//------------------------------------------------------------------------------
