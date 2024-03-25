//
// Created by oldlonecoder on 24-01-27.
//

#include "Lexer/Token.h"



static std::string_view NullMsg { "No String" };


namespace lex
{





std::string_view TokenInfo::LocationInfo::operator()() const
{
    auto E = End;
    if(!Begin) return NullMsg;
    if (!E) E = Begin + Length;
    return {Begin,E};
}

[[maybe_unused]] std::string TokenInfo::LocationInfo::Position() const
{
    StrAcc Txt = "%d,%d";

    return { (Txt << Line << Column)() };
}


TokenInfo::~TokenInfo()
{
    delete NumData;
}

std::string TokenInfo::Details() const
{
    StrAcc Out;
    Out << '\'' << Color::Yellow << Loc() << Color::Reset << "' Primary Type:" << Color::DeepSkyBlue7 << Component::Name(Prim) << Color::Reset << "{" << Color::Turquoise4 <<  Component::Name(Sem) << Color::Reset << "}";
    return Out();
}

} // lex