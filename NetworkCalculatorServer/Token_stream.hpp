#ifndef TOKEN_STREAM_HPP_INCLUDED
#define TOKEN_STREAM_HPP_INCLUDED

#include "Token.hpp"
#include "Calculation.hpp"
#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

namespace Calculation
{
    class Token_stream
    {
    public:

        Token_stream() : ip{nullptr}, owns{false} { }
        Token_stream(istream& s) : ip{&s}, owns{false} { }
        Token_stream(istream* p) : ip{p}, owns{true} { }
        Token_stream(Token_stream& ts) : ip{ts.ip}, owns{false} { }
        ~Token_stream() { close(); }

        Token get();
        Token& current() { return ct; };
        void set_input(istream& s) { close(); ip = &s; owns = false; }
        void set_input(istream* p) { close(); ip = p; owns = true; }
        void clear() {ip->clear();}
        istream* ip;

    private:

        void close() { if (owns) delete ip; ip = nullptr; }


        bool owns;
        Token ct { Kind::end };
    };
}

#endif // TOKEN_STREAM_H_INCLUDED
