//
// Created by oldlonecoder on 24-01-27.
//

/******************************************************************************************
 *   Copyright (C) /.../2024 by Serge Lussier                                             *
 *   lussier.serge@gmail.com                                                              *
 *                                                                                        *
 *   Unless otherwise specified, all code in this project is written                      *
 *   by the author (Serge Lussier)                                                        *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply to the code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 *****************************************************************************************/

#pragma once
#include "ULexer/Token.h"

#include <AppBook/Util/Object.h>



namespace Lexical
{

class LEXER_API TokenTable : public Util::Object
{
    TokenData::Array Ref;
    TokenData::Array Product;


public:

    TokenTable() = default;
    TokenTable(Util::Object* Par, const std::string& TableName);
    ~TokenTable() override;

    TokenData Scan(const char* C);

    [[maybe_unused]] virtual size_t DeclareTable();
    TokenData::Array& Tokens() { return Ref; }
};

} // ULexer


