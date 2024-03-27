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
#include <AppBook/Book/SVScanner.h>

//#ifndef LEXER_LEXER_H
//#define LEXER_LEXER_H

namespace lex
{

class LEXER_API Lexer
{
    Book::SVScanner Scanner{};
public:

    struct LEXER_API ConfigData
    {
        std::string_view Text{};
        TokenTable*      Production{nullptr};
    };
    ConfigData& Config() { return mConfig; }

    Lexer() = default;
    ~Lexer() = default;

    Book::Result operator()();
    Book::Result operator()(Lexer::ConfigData&& CfgData);



private:

    void UpdateTokenLocation(TokenInfo& NewToken);
    Book::Result Engage();
    Book::Result Tokenize(TokenInfo);

    ConfigData mConfig;

    Book::Result TokenizeIdentifier    (TokenInfo &NewToken);
    Book::Result TokenizeBinaryOperator(TokenInfo&);
    Book::Result TokenizeDefault       (TokenInfo& NewToken);
    Book::Result TokenizeUnaryOperator (TokenInfo& NewToken);
    Book::Result TokenizePunctuation   (TokenInfo& NewToken);
    Book::Result TokenizeKeyword       (TokenInfo& NewToken);
    Book::Result TokenizeString        (TokenInfo& NewToken);
    Book::Result TokenizeSignPrefix    (TokenInfo& NewToken);
    Book::Result TokenizePrefix        (TokenInfo& NewToken);
    Book::Result TokenizePostfix       (TokenInfo& NewToken);
    Book::Result TokenizeCppComment    (TokenInfo& NewToken);
    Book::Result TokenizeCommentBloc   (TokenInfo& NewToken);
    TokenInfo::Array& Production();

    void PushToken(TokenInfo& Token);
};

} // lex

//#endif //LEXER_LEXER_H
