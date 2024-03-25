//
// Created by oldlonecoder on 24-03-08.
//

#include "Lexer/Lexer.h"

namespace lex
{
Book::Result Lexer::operator()()
{
    return Engage();
}

Book::Result Lexer::operator()(Lexer::ConfigData &&CfgData)
{
    mConfig = CfgData;

    return Engage();
}

Book::Result Lexer::Engage()
{
    Book::Debug() << " Verify config data:";
    if(!mConfig.Production)
    {
        AppBook::Error() << " Config data is empty!";
        return Book::Result::Null_ptr;
    }

    mConfig.Production->DeclareTable();
    if(mConfig.Text.empty() || mConfig.Production->TokensRef().empty())
    {
        AppBook::Error() << " Config data is empty!";
        return Book::Result::Empty;
    }

    Book::Debug() << " Now Building the Tokens Reference Table:";

    Book::Debug() << " Here is the Ref Table Dump:" ;
    mConfig.Production->DebugDumpRef();

    //return Book::Result::Ok;

    Scanner = mConfig.Text;
    Scanner.SkipWS();
    std::string_view::iterator Stop{nullptr}; // Save current position.
    Book::Debug() << "Before entering the loop: ";
    Book::Out() << " Scanner stopped at {" << Book::Fn::Endl << Scanner() << Book::Fn::Endl << "}";
    Book::Test() << " Stop...";
    return Book::Result::Ok;

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

    return Book::Result::Accepted;
}

Book::Result Lexer::Tokenize(TokenInfo Token)
{
    static std::map<lex::Type::T, Book::Result (Lexer::*)(TokenInfo&)> ScanFn={
        {Type::Binary   , &Lexer::TokenizeBinaryOperator},
        {Type::Null     ,&Lexer::TokenizeDefault},
        {Type::Unary    ,&Lexer::TokenizeUnaryOperator},
        {Type::Punc     ,&Lexer::TokenizePunctuation},
        {Type::Keyword  ,&Lexer::TokenizeKeyword},
//        {Type::Hex      ,&Lexer::TokenizeHex},
        {Type::Text     ,&Lexer::TokenizeText},
//        {Type::Number   ,&Lexer::TokenizeNumber},
//        {Type::Id       ,&Lexer::TokenizeIdentifier},
        {Type::Prefix   ,&Lexer::TokenizePrefix},
        {Type::Postfix  ,&Lexer::TokenizePostfix},
        {Type::LineComment,&Lexer::TokenizeCppComment},
        {Type::BlocComment,&Lexer::TokenizeCommentBloc}
    };

    Book::Result R{};
    for(auto [T, Fn] : ScanFn)
    {
        if((T & Token.Sem) || (T & Token.Prim))
        {
            if(!(R = (this->*Fn)(Token)))
                return R;
        }
    }
    return R;
}

Book::Result Lexer::TokenizeBinaryOperator(TokenInfo &Token)
{
    //AppBook::Error() << " Une erreur est survenue..." << Book::Fn::Endl << Mark();
    PushToken(Token); // S'occupera de mettre à jour le token et d'avancer le SVScanner. ;)


    return Book::Result::Ok;
}

Book::Result Lexer::TokenizeDefault(TokenInfo &NewToken)
{

    auto R = Scanner.ScanNumber();
    if(!!R.first)
    {
        NewToken.NumData = new Book::SVScanner::Numeric::Details{R.second};
        NewToken.Loc = {
            .Offset = static_cast<size_t>(NewToken.Loc.Begin - Scanner.Begin()),
            .Length = NewToken.NumData->Seq.length(),
            .Begin  = NewToken.NumData->Seq.begin(),
            .End    = NewToken.NumData->Seq.end(),
        };
//        NewToken.Loc.Begin  = NewToken.NumData->Seq.begin();
//        NewToken.Loc.End    = NewToken.NumData->Seq.end();
//        NewToken.Loc.Length = NewToken.NumData->Seq.length();
//        NewToken.Loc.Offset = NewToken.Loc.Begin - Scanner.Begin();
        PushToken(NewToken);
    }
    else
        return R.first;

    return Book::Result::Accepted;
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
    auto A = Scanner(); // Prendre la position courante.

loop_id_scan:
    while(!Scanner.Eof(A) && std::isalpha(*A)) ++A;
    if(Scanner.Eof(A))
    {
        PushToken(NewToken);
        return Book::Result ::Accepted;
    }
    if(std::isalnum(*A) || (*A=='_')){ ++A; goto loop_id_scan;}

    if(A == Scanner()) return Book::Result::Rejected;

    Scanner.Sync();
    Scanner.Reposition(A-Scanner());
    NewToken.Loc = {
        .Line   = Scanner.Location().Line,
        .Column = Scanner.Location().Col,
        .Offset = static_cast<size_t>(Scanner() - Scanner.Begin()),
        .Length = static_cast<size_t>(A - Scanner()),
        .Begin = Scanner(),
        .End   = A
    };


    PushToken(NewToken);
    return Book::Result::Accepted;
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

void Lexer::PushToken(TokenInfo &Token)
{
    (*mConfig.Production) << Token;
    Scanner.Reposition(static_cast<int>(Token.Loc.Length));
    Scanner.SkipWS();
}


} // lex