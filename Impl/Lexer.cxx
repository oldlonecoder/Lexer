//
// Created by oldlonecoder on 24-03-08.
//

#include "Lexer/Lexer.h"

namespace lex
{



Book::Result Lexer::Execute()
{
    Book::Debug() << " Verify config data:";
    if(!mConfig.Production)
    {
        AppBook::Error() << " Config data is empty!";
        return Book::Result::Null_ptr;
    }



    Book::Debug() << " Now Building the Tokens Reference Table:";
    mConfig.Production->DeclareTable();
    if(mConfig.Text.empty() || mConfig.Production->TokensRef().empty())
    {
        AppBook::Error() << " Config data is empty!";
        return Book::Result::Empty;
    }

    Book::Debug() << " Here is the Ref Table Dump:" ;
    mConfig.Production->DebugDumpRef();

    //return Book::Result::Ok;

    Scanner = mConfig.Text;
    Scanner.SkipWS();

    return Loop();
}


/*!
 * @brief Virtual Loop
 *
 * @return Book::Result::Code...
 */
Book::Result Lexer::Loop()
{
    Book::Debug() << "Before entering the loop: ";
    Book::Out() << " Scanner position set at (col:" << Scanner()-Scanner.Begin() << "):{" << Scanner.Mark() << Book::Fn::Endl << "}";
    Book::Test() << " Now Entering in the loop:";
    //return Book::Result::Ok;
    auto Cursor = Scanner(); // Save current position.
    while(!Scanner.Eof() && (State != Book::Result::Eof))
    {
        Book::Debug() << " Lexer::Loop: " << Scanner.Mark();

        if(!Tokenize(mConfig.Production->Scan(Scanner()))) // Returned Eof!! WTF?
        {
            if(Scanner.Eof() || (State == Book::Result::Eof)) return Book::Result::Accepted;
            AppBook::Status() << " Lexer Rejected Token at: " << Book::Fn::Endl << Scanner.Mark();
            return Book::Result::Rejected;
        }
        if(Cursor == Scanner())
        {
            AppBook::Error() << " loop: No Scanning (unhandled yet or bug ;) )" << Book::Fn::Endl << Scanner.Mark();
            return Book::Result::Rejected;
        }

        Cursor = Scanner();
    }

    return Book::Result::Accepted;

}




Book::Result Lexer::Tokenize(TokenInfo Token)
{
    Book::Debug() << " :" << (Token ? Token.Details() : Scanner.Mark());

    static std::map<lex::Type::T, Book::Result (Lexer::*)(TokenInfo&)> ScanFn = {
        {Type::Binary           , &Lexer::TokenizeBinaryOperator},
        {Type::Null             , &Lexer::TokenizeDefault},
        {Type::Unary            , &Lexer::TokenizeUnaryOperator},
        {Type::Punc             , &Lexer::TokenizePunctuation},
        {Type::Keyword          , &Lexer::TokenizeKeyword},
        {Type::Text             , &Lexer::TokenizeString},
        {Type::Prefix           , &Lexer::TokenizePrefix},
        {Type::Postfix          , &Lexer::TokenizePostfix},
        {Type::LineComment      , &Lexer::TokenizeCppComment},
        {Type::BlocComment      , &Lexer::TokenizeCommentBloc}
    };

    Book::Result R{Book::Result::Rejected};
    for(auto [T, Fn] : ScanFn)
    {
        if(T & Token.Sem)
           return (this->*Fn)(Token);
    }
    return R;
}




Book::Result Lexer::TokenizeBinaryOperator(TokenInfo &NewToken)
{
    Book::Debug() << NewToken.Details() << Scanner.Mark();

    NewToken.Loc = Scanner.Sync();
    Scanner.Step(static_cast<int32_t>(NewToken.Loc.Length));
    PushToken(NewToken); // S'occupera de mettre à jour le token et d'avancer le TScanner. ;)

    return Book::Result::Accepted;
}

Book::Result Lexer::TokenizeDefault(TokenInfo &NewToken)
{
    Book::Debug() << " Entering with:" << (NewToken ? NewToken.Details() : Scanner.Mark());

    Book::Debug() << " Test ScanNumber:";
    auto R = Scanner.ScanNumber();
    if(!!R.first)
    {
        NewToken.NumData = new Book::TScanner::Numeric::Details{R.second};
        NewToken.Loc = Scanner.Sync();
        NewToken.Loc.Length = NewToken.NumData->Seq.length();
        NewToken.Loc.Begin  = NewToken.NumData->Seq.begin();
        NewToken.Loc.End    = NewToken.NumData->Seq.end();
        NewToken.Prim       = Type::Number;
        NewToken.Name       = lex::Lexem::Numeric;
        State = Scanner.Step(static_cast<int32_t>(NewToken.NumData->Seq.length()));
        NewToken.NumericTr();
        (*mConfig.Production) << NewToken;
        State = Scanner.SkipWS() ? Book::Result::Eof : Book::Result::Ok;
        Book::Debug() << "Pushed: " << NewToken.Details();
    }
    else
    {
        auto [Ic,C] = Book::Enums::CodeAttributes(R.first);
        Book::Debug() << " ScanNumber:" << C << Ic << Book::Enums::CodeText(R.first);
        Book::Debug() << " Test Scan Identifier Token:";
        return TokenizeIdentifier(NewToken);
    }
    return Book::Result::Accepted;
}


Book::Result Lexer::TokenizeUnaryOperator(TokenInfo &NewToken)
{
    NewToken.Loc = Scanner.Sync();
    State = Scanner.Step(static_cast<int32_t>(NewToken.Loc.Length));
    Book::Debug() << NewToken.Details();
    return Book::Result::Accepted;
}

Book::Result Lexer::TokenizePunctuation(TokenInfo &NewToken)
{
    Book::Debug() << " Sync'ing the Scanner:";
    NewToken.Loc = Scanner.Sync();
    //NewToken.Loc.Begin = Scanner();
    //NewToken.Loc.End = NewToken.Loc.Begin + NewToken.Loc.Length-1;
    //NewToken.Name    = NewToken.Loc();
    Book::Debug() << "Pushing New [Punctuation] Token";
    State = Scanner.Step(static_cast<int32_t>(NewToken.Loc.Length));
    PushToken(NewToken);
    return Book::Result::Accepted;
}

Book::Result Lexer::TokenizeKeyword(TokenInfo &NewToken)
{
    Book::Debug() << " Sync'ing the Scanner:";
    NewToken.Loc = Scanner.Sync();
    //NewToken.Loc.Begin = Scanner();
    //NewToken.Loc.End = NewToken.Loc.Begin + NewToken.Loc.Length-1;
    //NewToken.Name    = NewToken.Loc();
    State = Scanner.Step(static_cast<int32_t>(NewToken.Loc.Length));
    Book::Debug() << "Pushing New [Keyword] Token";
    PushToken(NewToken);
    return Book::Result::Accepted;
}


Book::Result Lexer::TokenizeString(TokenInfo &NewToken)
{
    return Book::Result::Ok;
}


Book::Result Lexer::TokenizeIdentifier(TokenInfo &NewToken)
{
    Book::Debug() << Scanner(); //Scanner.Mark();
    auto I = Scanner.ScanIdentifier();
    if(!I.first) return I.first;

//    auto I = Scanner.Scan([this](){
//
//        auto Start = Scanner();
//        if(! std::isalpha(*Scanner()) && (*Scanner() != '_'))
//            return Book::Result::Rejected;
//
//        State = ++Scanner ? Book::Result::Ok : Book::Result::Eof;
//
//        while(!Scanner.Eof() && (std::isalnum(*Scanner()) || (*Scanner() == '_'))) ++Scanner;
//        if(Start < Scanner())
//            return Book::Result::Accepted;
//
//        return Book::Result::Rejected;
//    });
//
//    if(!I.first)
//        return Book::Result::Rejected;

    Book::Debug() << " Fill NewToken Numeric literal Infos (Scanner's LocationData -> NewToken::LocationInfo):";
    NewToken.Loc = Scanner.Sync();
    NewToken.Loc.Length = I.second.length();
    NewToken.Loc.Begin = I.second.begin();
    NewToken.Loc.End = I.second.end() - 1;
    NewToken.Name    = lex::Lexem::Identifier;
    NewToken.Prim    = Type::Id;
    NewToken.Sem     = Type::Id|Type::Leaf;
    NewToken.Flags = { .V = 1 };
    Book::Debug() << "Pushing New [Identifier] Token";
    (*mConfig.Production) << NewToken;
    Scanner.Step(static_cast<int32_t>(NewToken.Loc.Length));
    Scanner.SkipWS();
    Book::Debug() << "Pushed: " << NewToken.Details();

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
void Lexer::PushToken(TokenInfo &NewToken)
{
    Book::Debug() << " Pushing NewToken : " << NewToken.Details();

    (*mConfig.Production) << NewToken;
    Book::Debug() << "Pushed NewToken:" << mConfig.Production->Product.back().Details();
    //Scanner.Sync(NewToken.Loc.Length);
    Book::Debug() << "SkipWS: ";
    Scanner.SkipWS();
}

TokenInfo::Array& Lexer::Production()
{
    return mConfig.Production->Ref;
}

void Lexer::UpdateTokenLocation(TokenInfo &NewToken)
{

}




} // lex