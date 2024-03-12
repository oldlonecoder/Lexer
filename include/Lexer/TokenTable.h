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
#include "Lexer/Token.h"

#include <AppBook/Util/Object.h>



namespace lex
{

class LEXER_API TokenTable : public Util::Object
{
    TokenInfo::Array Ref;
    TokenInfo::Array Product;


public:

    TokenTable() = default;
    TokenTable(Util::Object* Par, const std::string& TableName);
    ~TokenTable() override;

    TokenInfo Scan( TokenInfo::SVIterator C);

    [[maybe_unused]] virtual size_t DeclareTable();
    TokenInfo::Array& TokensRef() { return Ref; }

    TokenTable& operator << (TokenInfo& NewToken);
};

} // ULexer


