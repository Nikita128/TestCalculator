#ifndef TOKEN_STREAM_H_INCLUDED
#define TOKEN_STREAM_H_INCLUDED

#include <iostream>
#include "Token.h"
#include "Calculation.h"
#include <string>
#include <map>
#include <cctype>

using namespace std;

class Token_stream
{
public:

    Token_stream(istream& s) : ip{&s}, owns{false} { }
    Token_stream(istream* p) : ip{p}, owns{true} { }
    ~Token_stream() { close(); }

    Token get();
    Token& current() { return ct; };
    void set_input(istream& s) { close(); ip = &s; owns = false; }
    void set_input(istream* p) { close(); ip = p; owns = true; }

private:

    void close() { if (owns) delete ip; }

    istream* ip;
    bool owns;
    Token ct { Kind::end };
};

#endif // TOKEN_STREAM_H_INCLUDED
