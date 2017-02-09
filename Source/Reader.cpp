//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Reader.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#pragma hdrstop
#include "Reader.h"
#include "Group.h"
#include "Label.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read
void Reader::read(const string &filename, Game &game) {
    try {
        ifstream in(filename.c_str());
        if (!in.good()) {
            throw string("Error : Invalid file name = " + filename);
        }
        string token;
        in >> token;
        Label::read(in, token, game);
    }
    catch (string s) {
        cout << s << endl;
    }
    catch (...) {
        cout << "Error : Unknown exception caught in reader" << endl;
    }
}

//------------------------------------------------------------------------------
// read comment
bool Reader::comment(istream &in, string &token) {
    if (token == OPENING_COMMENT) {
        in >> token;
        while (token != CLOSING_COMMENT) {
            in >> token;
        }
        in >> token;
        return true;
    }
    else if (token == LINE_COMMENT) {
        getline(in, token);
        in >> token;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
