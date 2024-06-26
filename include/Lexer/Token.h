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
#include <AppBook/Book/TScanner.h>

namespace lex
{

struct LEXER_API TokenInfo
{
    using Array      = std::vector<TokenInfo>;
    using Iterator   = TokenInfo::Array::iterator;
    using CIterator  = TokenInfo::Array::const_iterator;


    Type::T     Prim = Type::Null;
    Type::T     Sem  = Type::Null;
    Mnemonic::T M    = Mnemonic::Noop;
    std::string_view Name{"Mnemonic::Undefined"}; // Pas vraiment le choix d'ajouter ça ici...
    Oper::T     D = Oper::Identifier;

    ~TokenInfo();

    // From Book::TScanner :
    Book::TScanner::Numeric::Details* NumData{nullptr};
    void NumericTr();
    // ------------------------------------------------

    struct LEXER_API LocationInfo
    {
        [[maybe_unused]] size_t Line{0};
        [[maybe_unused]] size_t Column{0};
        [[maybe_unused]] size_t Offset{0};
        [[maybe_unused]] size_t Length{0};
        const char* Begin{};
        const char* End{};
        std::string_view operator()();
        [[maybe_unused]] [[nodiscard]] std::string Position() const;
        TokenInfo::LocationInfo& operator = (Book::TScanner::LocationData const& Data);

    }Loc;


    struct LEXER_API TFlags
    {
        uint8_t V : 1;// This token is a usable value into expression.
        uint8_t S:  1;// Post semantic parser: Left-Assignable Object
        uint8_t M : 1;// Virtual multiply operator. ( ex.: "4ac" => 4*a*c )
                      //                                             ^<...
        uint8_t U : 1;// This token is a single utf-8 symbol { ex.:π,➪, ... }
    }Flags{0};

    explicit operator bool() const { return Loc.Begin != nullptr; }
    bool operator||(Type::T Sem_) const { return Sem || Sem_; }

    [[nodiscard]] std::string_view Text() const
    {
        if ((Flags.M) && (M == Mnemonic::Mul))
            return Lexem::Multiply;
        /* Overwrite source location. */
        if(!Loc.Length)
            return Loc.Begin; // This token is a ref token.

        return {Loc.Begin, Loc.Length};
    }



    [[nodiscard]] bool HasType(Type::T Ty) const{ return Sem & Ty; }
    [[nodiscard]] std::string Details(bool Frame=false) const;

};

}

