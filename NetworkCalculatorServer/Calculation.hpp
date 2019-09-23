#ifndef CALCULATION_HPP_INCLUDED
#define CALCULATION_HPP_INCLUDED

#include "Token.hpp"
#include "Token_stream.hpp"
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <cmath>
#include <sstream>

using namespace std;

namespace Calculation
{
    class Token_stream;
    class Calculator
    {
    public:
        Calculator() : ts{nullptr} { };
        Calculator(Token_stream* stream) : ts{stream} { };
        map<string,double> table;

        void set_token_stream(Token_stream& s) { ts = &s; }
        //void calculate();
        string calculate();

    private:
        Token_stream* ts;

        double expr(bool get);
        double term(bool get);
        double pow(bool get);
        double prim(bool get);
    };

    double error(const string& s);
}

#endif // CALCULATION_H_INCLUDED
