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
        {Type::Text     ,&Lexer::TokenizeString},
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

    PushToken(NewToken);
    return Book::Result::Ok;
}


Book::Result Lexer::TokenizeString(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}


Book::Result Lexer::TokenizeIdentifier(TokenInfo &NewToken)
{
    std::string_view::iterator A = Scanner(); // Prendre la position courante.

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
    if ((NewToken.M != Mnemonic::Sub) && (NewToken.M != Mnemonic::Add) &&
        (!mConfig.Production->TokensRef().empty()) &&
        (!mConfig.Production->TokensRef().back().HasType(Type::Binary | Type::Punc))
    )
        return Book::Result::Rejected;

    NewToken.Prim = Type::Prefix;
    NewToken.Sem &= ~Type::Postfix | Type::Postfix;
    NewToken.Loc.Length = 1;
    NewToken.Loc.End = NewToken.Loc.Begin + 1;
    PushToken(NewToken);
    return Book::Result::Accepted;
}



/*!
 * @brief Tokenize prefix operator after verifying that the prefix-operator is well formed and does not break the arithmetic syntax rules
 * @param NewToken
 *
 * @note a * *B;
 * @return Book::Result::Code
 */
Book::Result Lexer::TokenizePrefix(TokenInfo &NewToken)
{
    if ((NewToken.M == Mnemonic::Decr) || (NewToken.M == Mnemonic::Incr) || (NewToken.M == Mnemonic::BinaryNot))
    {
        if(Production().empty())
        {
            PushToken(NewToken);
            return Book::Result::Accepted;
        }
        if((Production().back().Flags.V) && (!Production().back().HasType(Type::Operator)))
        {
            NewToken.Prim = Type::Postfix;
            NewToken.Sem &= ~Type::Prefix | Type::Postfix;
            if(NewToken.M == Mnemonic::BinaryNot)
                NewToken.M = Mnemonic::Factorial;
        }
        if(!Production().back().Flags.V)
            throw AppBook::Exception()[AppBook::Syntax() << NewToken.Details() << ": Illegal;"];
    }
    PushToken(NewToken);
    return Book::Result::Accepted;
}




Book::Result Lexer::TokenizePostfix(TokenInfo &NewToken)
{

    if((Production().empty()) || (!Production().back().Flags.V))
        throw AppBook::Exception()[AppBook::Syntax() << NewToken.Details() << ": Illegal;"];

    PushToken(NewToken);
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


/*!
 * @brief
 * @param Token
 *
 * @todo Assign location data here.
 */
void Lexer::PushToken(TokenInfo &Token)
{
    ///@TODO Assign location data here.

    (*mConfig.Production) << Token;
    Scanner.Reposition(static_cast<int>(Token.Loc.Length));
    Scanner.SkipWS();
}

TokenInfo::Array& Lexer::Production()
{
    return mConfig.Production->Ref;
}


} // lex