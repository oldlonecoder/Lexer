//
// Created by oldlonecoder on 24-01-27.
//

#include "Lexer/Token.h"

namespace lex
{

std::string_view TokenData::TLocation::operator()() const
{
    return {Begin,End};
}

[[maybe_unused]] std::string TokenData::TLocation::Position() const
{
    StrAcc Txt = "%d,%d";

    return { (Txt << Line << Column)() };
}


} // lex