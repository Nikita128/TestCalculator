#ifndef CALCULATION_H_INCLUDED
#define CALCULATION_H_INCLUDED

#include "Token.h"
#include "Token_stream.h"
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

namespace Calculation
{
    class Token_stream;
    class Calculator
    {
    public:
        Calculator(Token_stream* stream) : ts{stream} { };
        map<string,double> table;

        void calculate();

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
