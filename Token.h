#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>

using namespace std;

enum class Kind : char
{
    name, number, end,
    plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
};

struct Token
{
    Kind kind;
    string string_value;
    double number_value;
};

#endif // TOKEN_H_INCLUDED
