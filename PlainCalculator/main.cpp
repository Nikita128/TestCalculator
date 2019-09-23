#include "Token_stream.h"
#include <sstream>
#include <iostream>
#include <map>
#include <thread>
#include "Calculation.h"

using namespace std;
using namespace Calculation;

int main(int argc, char* argv[])
{
    Calculation::Token_stream ts {cin};
    switch (argc)
    {
        case 1:
            break;
        case 2:
            ts.set_input(new istringstream{argv[1]});
            break;
        default:
            Calculation::error("too many arguments");
        return 1;
    }

    Calculation::Calculator calculator {&ts};

    calculator.table["pi"] = 3.1415926535897932385;
    calculator.table["e"] = 2.7182818284590452354;

    calculator.calculate();

    return 0;
}
