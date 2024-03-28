//
// Created by oldlonecoder on 24-01-27.
//

#include "Lexer/Token.h"

#include <AppBook/Book/SVScanner.h>

static std::string_view NullMsg { "No String" };


namespace lex
{



std::map<Book::SVScanner::Numeric::Details::SizeType, Type::T> NumMap =
{
    {Book::SVScanner::Numeric::Details::SizeType::I8  , Type::I8  },
    {Book::SVScanner::Numeric::Details::SizeType::I16 , Type::I16 },
    {Book::SVScanner::Numeric::Details::SizeType::I32 , Type::I32 },
    {Book::SVScanner::Numeric::Details::SizeType::I64 , Type::I64 },
    {Book::SVScanner::Numeric::Details::SizeType::U8  , Type::U8  },
    {Book::SVScanner::Numeric::Details::SizeType::U16 , Type::U16 },
    {Book::SVScanner::Numeric::Details::SizeType::U32 , Type::U32 },
    {Book::SVScanner::Numeric::Details::SizeType::U64 , Type::U64 },
    {Book::SVScanner::Numeric::Details::SizeType::F32 , Type::F32 },
    {Book::SVScanner::Numeric::Details::SizeType::F64 , Type::F64 },
    {Book::SVScanner::Numeric::Details::SizeType::F128, Type::F128}
};

std::string_view TokenInfo::LocationInfo::operator()() const
{
    if(!Begin) return NullMsg;
    Book::Debug() << " Length: " << Length;
    return {Begin,Length ? Length : Length+1};
}

[[maybe_unused]] std::string TokenInfo::LocationInfo::Position() const
{
    StrAcc Txt = "%d,%d";
    return { (Txt << Line << Column)() };
}

TokenInfo::LocationInfo &TokenInfo::LocationInfo::operator=(const Book::SVScanner::LocationData &Data)
{
    Line   = Data.Line;
    Column = Data.Col;
    Offset = Data.Offset;
    return *this;
}


TokenInfo::~TokenInfo()
{
    delete NumData;
}

std::string TokenInfo::Details() const
{
    StrAcc Out;
    Out << '\'' << Color::Yellow << Text() <<
        Color::Reset << "' [" <<
        Color::Yellow << Name <<
        Color::Reset << "] Primary Type:" <<
        Color::DeepSkyBlue7 << Component::TypeName(Prim) <<
        Color::Reset << "{" <<
        Color::Turquoise4 << Component::TypeName(Sem) <<
        Color::Reset << "}";

    return Out();
}

void TokenInfo::NumericTr()
{
    if(!NumData)
        throw AppBook::Exception() [Book::Error() << " Cannot call TokenInfo::NumericTr on un-scanned or non-numeric token."];
    Sem |= Type::Number | Type::Const | NumMap[NumData->Size] | Type::Leaf;
}


} // lex