#ifndef CALCULATION_H_INCLUDED
#define CALCULATION_H_INCLUDED

#include <iostream> // I/O
#include <string> // strings
#include <map> // map
#include <cctype> // isalpha(), etc.
#include "Token_stream.h"
#include "Token.h"

using namespace std;

double expr(bool get);
double term(bool get);
double prim(bool get);
double error(const string& s);
void calculate();

#endif // CALCULATION_H_INCLUDED
