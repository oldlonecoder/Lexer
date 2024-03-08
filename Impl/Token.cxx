//
// Created by oldlonecoder on 24-01-27.
//

#include "Lexer/Token.h"

namespace lex
{

std::string_view TokenInfo::LocationInfo::operator()() const
{
    return {Begin,End};
}

[[maybe_unused]] std::string TokenInfo::LocationInfo::Position() const
{
    StrAcc Txt = "%d,%d";

    return { (Txt << Line << Column)() };
}


} // lex