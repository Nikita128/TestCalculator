#include "Calculation.h"

extern Calculation::Token_stream ts;
extern map<string,double> table;
extern mutex stream_mutex;
using namespace Calculation;

double Calculator::expr(bool get)
{
    double left = term(get);
    for (;;)
    {
        switch (ts->current().kind)
        {
            case Kind::plus:
                left += term(true);
                break;
            case Kind::minus:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}

double Calculator::term(bool get)
{
    double left = pow(get);
    for (;;)
    {
        switch (ts->current().kind)
        {
            case Kind::mul:
                left *= pow(true);
                break;
            case Kind::div:
                if (auto d = pow(true))
                {
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}

double Calculator::pow(bool get)
{
    double left = prim(get);
    for (;;)
    {
        switch (ts->current().kind)
        {
            case Kind::pow:
                left = std::pow(left, prim(true));
                break;
            default:
                return left;
        }
    }
}

double Calculator::prim(bool get)
{
    if (get) ts->get();
    switch (ts->current().kind)
    {
        case Kind::number:
        {
            double v = ts->current().number_value;
            ts->get();
            return v;
        }
        case Kind::name:
        {
            double& v = table[ts->current().string_value];
            if (ts->get().kind == Kind::assign) v = expr(true);
            return v;
        }
        case Kind::minus:
            return -prim(true);
        case Kind::lp:
        {
            auto e = expr(true);
            if (ts->current().kind != Kind::rp) return error("')' expected");
            ts->get();
            return e;
        }
        default:
            return error("primary expected");
    }
}

void Calculator::calculate()
{
    for (;;)
    {

        ts->get();

        if (ts->current().kind == Kind::end) break;
        if (ts->current().kind == Kind::print) continue;

        cout << expr(false) << '\n';
    }
}

double Calculation::error(const string& s)
{
    cerr << "error: " << s << '\n';
    return 1;
}
