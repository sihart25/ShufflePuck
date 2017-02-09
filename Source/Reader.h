//------------------------------------------------------------------------------
//
// Module 08937 : Virtual Environments
// ShufflePuck Assessment
// Reader.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Reader_h
#define Reader_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Label.h"
#include "Game.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const char OPENING_BRACE[] = "{";
    const char CLOSING_BRACE[] = "}";
    const char OPENING_COMMENT[] = "/*";
    const char CLOSING_COMMENT[] = "*/";
    const char LINE_COMMENT[] = "//";

    //------------------------------------------------------------------------------
    // class definition

    class Reader {

    public:

        static void read(const string &filename, Game &game);
        static bool comment(istream &in, string &token);

    private:

    };

} // ComputerGraphics

#endif // Reader_h

//------------------------------------------------------------------------------
