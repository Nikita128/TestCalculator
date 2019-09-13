#include "Token_stream.h"

using namespace std;

Token Token_stream::get()
{
    char ch;

    do { // skip whitespace except ’\n’
        if (!ip->get(ch)) return ct = { Kind::end };
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case 0:
            return ct = { Kind::end }; // assign and return
        case ';':
        case '\n':
            return ct={ Kind::print };
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
            ip->putback(ch); //put the first digit (or .) back into the input stream
            *ip >> ct.number_value; // read number into ct
            ct.kind = Kind::number;
            return ct;
        default: //name, name =, or error
            if (isalpha(ch)) {
                ct.string_value = ch;
                while (ip->get(ch) && isalnum(ch))
                    ct.string_value += ch; // append ch to end of string_value
                ip->putback(ch);
                ct.kind = Kind::name;
                return ct;
            }
                error("bad token");
                return ct = {Kind::print};
            }
}
