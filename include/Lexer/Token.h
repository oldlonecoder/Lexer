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



#include "Lexer/Components.h"

#include <string_view>

namespace lex
{

struct LEXER_API TokenInfo
{
    using Array = std::vector<TokenInfo>;
    using Iterator  = TokenInfo::Array::iterator;
    using CIterator = TokenInfo::Array::const_iterator;
    using SVIterator  = std::string_view::iterator;

    Type::T     Prim = Type::Null;
    Type::T     Sem = Type::Null;
    Mnemonic::T M = Mnemonic::Noop;
    Oper::T     D = Oper::Identifier;
    struct LEXER_API LocationInfo
    {
        [[maybe_unused]] size_t Line{0};
        [[maybe_unused]] size_t Column{0};
        [[maybe_unused]] size_t Offset{0};
        [[maybe_unused]] size_t Length{0};
        TokenInfo::SVIterator Begin{};
        TokenInfo::SVIterator End{};
        std::string_view operator()() const;
        [[maybe_unused]] [[nodiscard]] std::string Position() const;
    }Loc;


    struct LEXER_API TFlags
    {
        uint8_t V : 1;// This token is a usable value into expression.
        uint8_t S:  1;// Post semantic parser: Left-Assignable Object
        uint8_t M : 1;// Virtual multiply operator. ( ex.: "4ac" => 4*a*c )
                      //                                             ^<...
        uint8_t U : 1;// This token is a single utf-8 symbol { ex.:π,➪, ... }
    }Flags{0};

    //SppToken* back_to_startof_line();

    explicit operator bool() const { return Loc.Begin != nullptr; }
    bool operator||(Type::T Sem_) const { return Sem || Sem_; }

    [[nodiscard]] std::string_view Text() const
    {
        if ((Flags.M) && (M == Mnemonic::Mul))
            return Lexem::Multiply;
        /* Overwrite source location. */
        return Loc();
    }

    [[nodiscard]] bool HasType(Type::T Ty){ return Sem & Ty; }

};

}

