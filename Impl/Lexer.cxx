//
// Created by oldlonecoder on 24-03-08.
//

#include "Lexer/Lexer.h"

namespace lex
{
Book::Result Lexer::operator()()
{
    return Book::Result::Ok;
}

Book::Result Lexer::operator()(Lexer::ConfigData &&CfgData)
{
    mConfig = CfgData;

    return Engage();
}

Book::Result Lexer::Engage()
{
    if(mConfig.Text.empty() || mConfig.Production->TokensRef().empty())
    {
        AppBook::Error() << " Config data is empty!";
        return Book::Result::Empty;
    }

    Scanner = mConfig.Text;
    Scanner.SkipWS();
    std::string_view::iterator Stop{nullptr}; // Save current position.
    while(!Scanner.Eof())
    {
        if(Stop == Scanner())
        {
            AppBook::Error() << " Infinite loop:" << Book::Fn::Endl << Scanner.Mark();
            return Book::Result::Rejected;
        }

        if(!Tokenize(mConfig.Production->Scan(Stop))) return Book::Result::Rejected;
        Stop = Scanner();
    }

    return Book::Result::Notimplemented;
}

Book::Result Lexer::Tokenize(TokenInfo Token)
{
    static std::map<lex::Type::T, Book::Result (Lexer::*)(TokenInfo&)> ScanFn={
        {Type::Binary   , &Lexer::TokenizeBinaryOperator},
        {Type::Null     ,&Lexer::TokenizeDefault},
        {Type::Unary    ,&Lexer::TokenizeUnaryOperator},
        {Type::Punc     ,&Lexer::TokenizePunctuation},
        {Type::Keyword  ,&Lexer::TokenizeKeyword},
        {Type::Hex      ,&Lexer::TokenizeHex},
        {Type::Text     ,&Lexer::TokenizeText},
        {Type::Number   ,&Lexer::TokenizeNumber},
        {Type::Id       ,&Lexer::TokenizeIdentifier},
        {Type::Sign     ,&Lexer::TokenizeSignPrefix},
        {Type::Prefix   ,&Lexer::TokenizePrefix},
        {Type::Postfix  ,&Lexer::TokenizePostfix},
        {Type::LineComment,&Lexer::TokenizeCppComment},
        {Type::BlocComment,&Lexer::TokenizeCommentBloc}
    };

    for(auto [T, Fn] : ScanFn)
    {
        if((T & Token.Sem) || (T & Token.Prim))
        {
            if(!(this->*Fn)(Token))
                return Book::Result::Rejected;
        }
    }
}

Book::Result Lexer::TokenizeBinaryOperator(TokenInfo &Token)
{
    //AppBook::Error() << " Une erreur est survenue..." << Book::Fn::Endl << Mark();
    PushToken(Token); // S'occupera de mettre à jour le token et d'avancer le SVScanner. ;)


    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeDefault(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeUnaryOperator(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizePunctuation(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeKeyword(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeHex(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeText(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeNumber(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeIdentifier(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeSignPrefix(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizePrefix(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizePostfix(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeCppComment(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeCommentBloc(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}


} // lex