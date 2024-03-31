//
// Created by oldlonecoder on 24-03-08.
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

#include "Lexer/TokenTable.h"
#include <AppBook/Book/TScanner.h>

//#ifndef LEXER_LEXER_H
//#define LEXER_LEXER_H

namespace lex
{

class LEXER_API Lexer
{
public:

    struct LEXER_API ConfigData
    {
        std::string_view Text{};
        TokenTable*      Production{nullptr};
    };
    ConfigData& Config() { return mConfig; }

    Lexer() = default;
    virtual ~Lexer() = default;

    virtual Book::Result Execute();




protected:
    Book::TScanner Scanner{};
    virtual Book::Result Loop();
    Book::Result  State{Book::Result::Ok};
    void PushToken(TokenInfo& Token);


    void UpdateTokenLocation(TokenInfo& NewToken);
    Book::Result Tokenize(TokenInfo);

    ConfigData mConfig;

    virtual Book::Result TokenizeIdentifier    (TokenInfo &NewToken);
    virtual Book::Result TokenizeBinaryOperator(TokenInfo&);
    virtual Book::Result TokenizeDefault       (TokenInfo& NewToken);
    virtual Book::Result TokenizeUnaryOperator (TokenInfo& NewToken);
    virtual Book::Result TokenizePunctuation   (TokenInfo& NewToken);
    virtual Book::Result TokenizeKeyword       (TokenInfo& NewToken);
    virtual Book::Result TokenizeString        (TokenInfo& NewToken);
    virtual Book::Result TokenizeSignPrefix    (TokenInfo& NewToken);
    virtual Book::Result TokenizePrefix        (TokenInfo& NewToken);
    virtual Book::Result TokenizePostfix       (TokenInfo& NewToken);
    virtual Book::Result TokenizeCppComment    (TokenInfo& NewToken);
    virtual Book::Result TokenizeCommentBloc   (TokenInfo& NewToken);
    TokenInfo::Array& Production();


};

} // lex

//#endif //LEXER_LEXER_H
