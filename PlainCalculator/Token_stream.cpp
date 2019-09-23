#include "Token_stream.h"

extern mutex stream_mutex;

using namespace std;
using namespace Calculation;

Token Token_stream::get()
{
    char ch;
    do {
        if (!ip->get(ch)) return ct = { Kind::end };
    } while (ch != '\n' && isspace(ch));
    switch (ch) {
        case 0:
            return ct = { Kind::end };
        case ';':
        case '\n':
            return ct= { Kind::print };
        case '^':
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return ct = { static_cast<Kind>(ch) };
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        case '.':
            ip->putback(ch);
            *ip >> ct.number_value;
            ct.kind = Kind::number;
            return ct;
        default:
            if (isalpha(ch))
            {
                ct.string_value = ch;
                while (ip->get(ch) && isalnum(ch))
                    ct.string_value += ch;
                ip->putback(ch);
                ct.kind = Kind::name;
                return ct;
            }
                Calculation::error("bad token");
                return ct = {Kind::print};
            }
}
