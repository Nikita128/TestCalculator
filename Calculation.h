#ifndef CALCULATION_H_INCLUDED
#define CALCULATION_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include "Token_stream.h"
#include "Token.h"

using namespace std;

double expr(bool get);
double term(bool get);
double prim(bool get);
double error(const string& s);
void calculate();

#endif // CALCULATION_H_INCLUDED
