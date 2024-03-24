//
// Created by oldlonecoder on 24-03-12.
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

#include <Lexer/Lexer.h>
#include <BookApplicationSkel/ApplicationSkel.h>

//#ifndef LEXER_TEST_H
//#define LEXER_TEST_H

namespace lex
{

class Test : public Book::ApplicationSkel
{

public:
    Test() = default;
    Test(const std::string& AppID, int argc=0, char** argv=nullptr);
    ~Test() override;

    Book::Result Run() override;
protected:
    Book::Result Setup() override;
};

} // lex

//#endif //LEXER_TEST_H
