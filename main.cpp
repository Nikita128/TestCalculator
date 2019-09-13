#include <sstream>
#include <iostream>
#include <map>
#include "Calculation.h"
#include "Token_stream.h"

using namespace std;

Token_stream ts {cin};
map<string,double> table;

int main(int argc, char* argv[])
{
    switch (argc)
    {
        case 1:
            break;
        case 2:
            ts.set_input(new istringstream{argv[1]});
            break;
        default:
            error("too many arguments");
        return 1;
    }

    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    calculate();

    return 0;
}
