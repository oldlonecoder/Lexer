//
// Created by oldlonecoder on 24-01-27.
//
#include "Lexer/TokenTable.h"
#include <AppBook/Book/AppBook.h>

namespace lex
{
/*!
 * @brief This is the default complete tokens reference of the Scrat Language.
 * @return
 */
[[maybe_unused]] size_t TokenTable::DeclareTable()
{
    Ref = TokenInfo::Array{
        {
            .Prim = Type::Binary,
            .Sem = Type::Operator|Type::Binary,
            .M     = Mnemonic::LeftShift,
            .Name  = {"Mnemonic::LeftShift"},
            .D     = Oper::Shift,
            .Loc   = { .Begin = Lexem::LeftShift },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword|Type::Number|Type::Const,
            .M     = Mnemonic::Null,
            .Name  = "Mnemonic::Null",
            .D     = Oper::Identifier,
            .Loc   = { .Begin = Lexem::Null },
            .Flags = { .V = 1 }
        },
        {
            .Prim  = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M     = Mnemonic::Unshadow,
            .Name  = "Mnemonic::Unshadow",
            .D     = Oper::Scope,
            .Loc   = { .Begin = Lexem::Unshadow },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::OpenPair,
            .Sem = Type::Binary|Type::Operator|Type::OpenPair|Type::Punc,
            .M     = Mnemonic::OpenAbsOp, // |< x+1 >|;
            //                               ~~
            //                               ^
            .Name  = "Mnemonic::OpenAbsOp",
            .D     = Oper::Parenthese,
            .Loc   = {.Begin = Lexem::AbsBegin },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::ClosePair,
            .Sem = Type::Binary|Type::Operator|Type::OpenPair|Type::Punc,
            .M     = Mnemonic::CloseAbsOp, // |< x+1 >|;
            //                                       ~~
            //                                       ^
            .Name  = "Mnemonic::CloseAbsOp",
            .D     = Oper::Parenthese,
            .Loc   = {.Begin = Lexem::AbsEnd },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Binary,
            .Sem = Type::Binary|Type::Operator,
            .M     = Mnemonic::Radical,
            .Name  = "Mnemonic::Radical",
            .D     = Oper::Exponent,
            .Loc   = {.Begin = Lexem::Radical },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Binary,
            .Sem = Type::Binary|Type::Operator,
            .M     = Mnemonic::Exponent,
            .Name    = "Mnemonic::Exponent",
            .D     = Oper::Exponent,
            .Loc   = {.Begin = Lexem::Exponent },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Binary,
            .Sem = Type::Binary|Type::Operator,
            .M     = Mnemonic::RightShift,
            .Name  = "Mnemonic::RightShift",
            .D     = Oper::Shift,
            .Loc   = {.Begin = Lexem::RightShift },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Binary,
            .Sem = Type::Binary|Type::Operator,
            .M     = Mnemonic::BinaryXor,
            .Name  = "Mnemonic::BinaryXor",
            .D     = Oper::Bits,
            .Loc   = {.Begin = Lexem::Xor },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Prefix|Type::Operator|Type::Unary,
            .M     = Mnemonic::Deref,
            .Name  = "Mnemonic::Deref",
            .D     = Oper::Deref,
            .Loc   = {.Begin = Lexem::Deref },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M     = Mnemonic::Deref,
            .Name  = "Mnemonic::DerefUtf",
            .D     = Oper::Bits,
            .Loc   = {.Begin = "➪" },
            .Flags = { .V = 1 }
        },
        {
            .Prim = Type::Unary,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M     = Mnemonic::Decr,
            .Name  = "Mnemonic::Decr",
            .D     = Oper::Unary,
            .Loc   = {.Begin = Lexem::Decr },
            .Flags = { .V = 1 }
        },
        {
            .Prim  = Type::Unary,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M     = Mnemonic::Incr,
            .Name  = "Mnemonic::Incr",
            .D     = Oper::Unary,
            .Loc   = {.Begin = Lexem::Incr },
            .Flags = { .V = 1 }
        },
        {
            .Prim  = Type::Assign,
            .Sem   = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M     = Mnemonic::AssignAdd,
            .Name  = "Mnemonic::AssignAdd",
            .D     = Oper::Assign,
            .Loc   = {.Begin = Lexem::AssignAdd},
            .Flags = {.V=1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignMul,
            .Name  = "Mnemonic::AssignMul",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignMul},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignDiv,
            .Name  = "Mnemonic::AssignDiv",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignDiv},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignMod,
            .Name  = "Mnemonic::AssignMod",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignMod},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignOr,
            .Name  = "Mnemonic::AssignOr",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignOr},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignXor,
            .Name  = "Mnemonic::AssignXor",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignXor},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignC1,
            .Name  = "Mnemonic::AssignC1",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignC1},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignLeftShift,
            .Name  = "Mnemonic::AssignLeftShift",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignLShift},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Assign,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::AssignRightShift,
            .Name  = "Mnemonic::AssignRightShift",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::AssignRShift},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::GreaterEq,
            .Name  = "Mnemonic::GreaterEq",
            .D      = Oper::Equality,
            .Loc    = {.Begin = Lexem::GreaterEqual},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::Equal,
            .Name  = "Mnemonic::Equal",
            .D      = Oper::Equality,
            .Loc    = {.Begin = Lexem::Equal},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::NotEqual,
            .Name  = "Mnemonic::NotEqual",
            .D      = Oper::Equality,
            .Loc    = {.Begin = Lexem::NotEqual},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::NotEqual,
            .Name  = "Mnemonic::NotEqualAlt",
            .D      = Oper::Equality,
            .Loc    = {.Begin = "<>"},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary,
            .M      = Mnemonic::Add,
            .Name  = "Mnemonic::Addition",
            .D      = Oper::Addition,
            .Loc    = {.Begin = Lexem::Addition},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary,
            .M      = Mnemonic::Sub,
            .Name  = "Mnemonic::Subtract",
            .D      = Oper::Addition,
            .Loc    = {.Begin = Lexem::Sub},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary,
            .M      = Mnemonic::Mul,
            .Name  = "Mnemonic::Multiply",
            .D      = Oper::Product,
            .Loc    = {.Begin = Lexem::Multiply},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::LineComment,
            .Sem    = Type::LineComment|Type::Operator,
            .M      = Mnemonic::CommentCpp,
            .Name  = "Mnemonic::CommentCpp",
            .D      = Oper::Noop_,
            .Loc    = {.Begin = Lexem::CommentCpp},
            .Flags  = {.V = 0}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary,
            .M      = Mnemonic::Modulo,
            .Name  = "Mnemonic::Modulo",
            .D      = Oper::Product,
            .Loc    = {.Begin = Lexem::Modulo},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::LessThan,
            .Name  = "Mnemonic::LessThan",
            .D      = Oper::Equality,
            .Loc    = {.Begin = Lexem::LessThan},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::GreaterThan,
            .Name  = "Mnemonic::GreaterThan",
            .D      = Oper::Equality,
            .Loc    = {.Begin = Lexem::GreaterThan},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Keyword|Type::Operator|Type::Binary|Type::Assign,
            .M      = Mnemonic::Assign,
            .Name  = "Mnemonic::Assign",
            .D      = Oper::Assign,
            .Loc    = {.Begin = Lexem::Assign},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary,
            .M      = Mnemonic::BinaryAnd,
            .Name  = "Mnemonic::BinaryAnd",
            .D      = Oper::Bits,
            .Loc    = {.Begin = Lexem::BinaryAnd},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary,
            .M      = Mnemonic::BinaryOr,
            .Name  = "Mnemonic::BinaryOr",
            .D      = Oper::Bits,
            .Loc    = {.Begin = Lexem::BinaryOr},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Prefix,
            .Sem    = Type::Unary|Type::Operator|Type::Prefix,
            .M      = Mnemonic::C2, // Tow's complement
            .Name  = "Mnemonic::TwoComplement",
            .D      = Oper::Prefix,
            .Loc    = {.Begin = Lexem::C2},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Prefix,
            .Sem    = Type::Unary|Type::Operator|Type::Prefix,
            .M      = Mnemonic::C1, // Tow's complement
            .Name  = "Mnemonic::OneComplement",
            .D      = Oper::Prefix,
            .Loc    = {.Begin = Lexem::C1},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Unary,
            .Sem    = Type::Unary|Type::Operator|Type::Prefix,
            .M      = Mnemonic::BinaryNot, // Tow's complement
            .Name  = "Mnemonic::BinaryNot",
            .D      = Oper::Prefix,
            .Loc    = {.Begin = Lexem::Not},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::LogicalAnd, // Tow's complement
            .Name  = "Mnemonic::LogicalAnd",
            .D      = Oper::Bool_and,
            .Loc    = {.Begin = Lexem::BoolAnd},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::Binary,
            .Sem    = Type::Operator|Type::Binary|Type::Bool,
            .M      = Mnemonic::LogicalOr, // Tow's complement
            .Name  = "Mnemonic::LogicalOr",
            .D      = Oper::Bool_or,
            .Loc    = {.Begin = Lexem::BoolOr},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::OpenPair,
            .Sem    = Type::Operator|Type::Punc|Type::OpenPair,
            .M      = Mnemonic::OpenPar, // Tow's complement
            .Name  = "Mnemonic::OpenPar",
            .D      = Oper::Parenthese,
            .Loc    = {.Begin = Lexem::OpenPar},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::ClosePair,
            .Sem    = Type::Operator|Type::Punc|Type::ClosePair,
            .M      = Mnemonic::ClosePar, // Tow's complement
            .Name  = "Mnemonic::ClosePar",
            .D      = Oper::Parenthese,
            .Loc    = {.Begin = Lexem::ClosePar},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::OpenPair,
            .Sem    = Type::Operator|Type::Punc|Type::OpenPair,
            .M      = Mnemonic::Openindex, // Tow's complement
            .Name  = "Mnemonic::OpenIndex",
            .D      = Oper::Parenthese,
            .Loc    = {.Begin = Lexem::OpenIndex},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::ClosePair,
            .Sem    = Type::Operator|Type::Punc|Type::ClosePair,
            .M      = Mnemonic::Closeindex, // Tow's complement
            .Name  = "Mnemonic::CloseIndex",
            .D      = Oper::Parenthese,
            .Loc    = {.Begin = Lexem::CloseIndex},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::OpenPair,
            .Sem    = Type::Operator|Type::Punc|Type::OpenPair,
            .M      = Mnemonic::Openbrace, // Tow's complement
            .Name  = "Mnemonic::OpenBrace",
            .D      = Oper::Parenthese,
            .Loc    = {.Begin = Lexem::BraceBegin},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::ClosePair,
            .Sem    = Type::Operator|Type::Punc|Type::ClosePair,
            .M      = Mnemonic::Closebrace, // Tow's complement
            .Name  = "Mnemonic::CloseBrace",
            .D      = Oper::Parenthese,
            .Loc    = {.Begin = Lexem::BraceEnd},
            .Flags  = {.V = 1}
        },
        {
            .Prim   = Type::BlocComment,
            .Sem    = Type::BlocComment|Type::Operator,
            .M      = Mnemonic::BeginComment, // Tow's complement
            .Name  = "Mnemonic::BeginBlocComment",
            .D      = Oper::Noop_,
            .Loc    = {.Begin = Lexem::CommentBegin},
            .Flags  = {.V = 0}
        },
        {
            .Prim   = Type::BlocComment,
            .Sem    = Type::BlocComment|Type::Operator,
            .M      = Mnemonic::EndComment, // Tow's complement
            .Name  = "Mnemonic::EndBlocComment",
            .D      = Oper::Noop_,
            .Loc    = {.Begin = Lexem::CommentEnd},
            .Flags  = {.V = 0}
        },
        {
            .Prim = Type::Binary,
            .Sem = Type::Operator|Type::Binary,
            .M = Mnemonic::Div,
            .Name  = "Mnemonic::Division",
            .D = Oper::Product,
            .Loc = {.Begin = Lexem::Division},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Punc,
            .Sem = Type::Operator|Type::Binary|Type::Punc,
            .M = Mnemonic::Comma,
            .Name  = "Mnemonic::Comma",
            .D = Oper::Comma,
            .Loc = {.Begin = Lexem::Comma},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Punc,
            .Sem = Type::Operator|Type::Binary|Type::Punc,
            .M = Mnemonic::Scope,
            .Name  = "Mnemonic::Scope",
            .D = Oper::Scope,
            .Loc = {.Begin = Lexem::Scope},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Punc,
            .Sem = Type::Punc,
            .M = Mnemonic::Semicolon,
            .Name  = "Mnemonic::SemiColon",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Semicolon},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Punc,
            .Sem = Type::Operator|Type::Binary|Type::Punc,
            .M = Mnemonic::Colon,
            .Name  = "Mnemonic::Colon",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Colon},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Binary,
            .Sem = Type::Operator|Type::Binary|Type::Punc,
            .M = Mnemonic::Range,
            .Name  = "Mnemonic::Range",
            .D = Oper::Scope,
            .Loc = {.Begin = Lexem::Range},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Postfix,
            .Sem = Type::Unary|Type::Postfix|Type::Operator,
            .M = Mnemonic::Factorial,
            .Name  = "Mnemonic::Factorial",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Factorial},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Sign|Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Positive,
            .Name  = "Mnemonic::Positive",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Positive},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Sign|Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Negative,
            .Name  = "Mnemonic::Negative",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Negative},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Text,
            .Sem = Type::Text|Type::Leaf|Type::Operator,
            .M = Mnemonic::Squote,
            .Name  = "Mnemonic::SingleQuote",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Squote},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Text,
            .Sem = Type::Text|Type::Leaf|Type::Operator,
            .M = Mnemonic::Dquote,
            .Name  = "Mnemonic::DoubleQuote",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Dquote},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword|Type::Operator|Type::Binary,
            .M = Mnemonic::Ternary,
            .Name  = "Mnemonic::Ternary",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Ternary},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Hash,
            .Name  = "Mnemonic::Hash",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Hash},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Eos,
            .Name  = "Mnemonic::EosMark",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Eos},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Punc,
            .Sem = Type::Punc|Type::Operator,
            .M = Mnemonic::Dot,
            .Name  = "Mnemonic::Dot",
            .D = Oper::Scope,
            .Loc = {.Begin = Lexem::Dot},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Return,
            .Name  = "Mnemonic::Return",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Return},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::If,
            .Name  = "Mnemonic::If",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::If},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Number,
            .Sem = Type::Number|Type::Leaf|Type::Float|Type::Keyword|Type::Const,
            .M = Mnemonic::Pi,
            .Name  = "Mnemonic::Pi",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Pi},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Number,
            .Sem = Type::Number|Type::Leaf|Type::Float|Type::Keyword|Type::Const,
            .M = Mnemonic::Pi,
            .Name  = "Mnemonic::PiUtf",
            .D = Oper::Identifier,
            .Loc = {.Begin = "π"},
            .Flags{.V=1,.U=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Number|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator,
            .M = Mnemonic::Number,
            .Name  = "Mnemonic::Number",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Number},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::U8|Type::Keyword|Type::Prefix|Type::Operator,
            .M = Mnemonic::U8,
            .Name  = "Mnemonic::U8",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::U8},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::U16|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator,
            .M = Mnemonic::U16,
            .Name  = "Mnemonic::U16",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::U16},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::U32|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator,
            .M = Mnemonic::U32,
            .Name  = "Mnemonic::U32",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::U32},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::U64|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator,
            .M = Mnemonic::U64,
            .Name  = "Mnemonic::U64",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::U64},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::I8|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator,
            .M = Mnemonic::I8,
            .Name  = "Mnemonic::I8",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::I8},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::I16|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator                ,
            .M = Mnemonic::I16,
            .Name  = "Mnemonic::I16",
            .D = Oper::Identifier, .Loc = {.Begin = Lexem::I16},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::I32|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator                ,
            .M = Mnemonic::I32,
            .Name  = "Mnemonic::I32",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::I32},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::I64|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator
            ,.M = Mnemonic::I64,
            .Name  = "Mnemonic::I64",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::I64},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Float|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator ,
            .M = Mnemonic::Float,
            .Name  = "Mnemonic::Float",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Float},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Text|Type::Unary|Type::Keyword|Type::Prefix|Type::Operator,
            .M = Mnemonic::String,
            .Name  = "Mnemonic::String",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::String},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Then,
            .Name  = "Mnemonic::Then",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Then},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Else,
            .Name  = "Mnemonic::Else",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Else},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword|Type::Const,
            .M = Mnemonic::Const,
            .Name  = "Mnemonic::Const",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Const},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Include,
            .Name  = "Mnemonic::Include",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Include},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Amu,
            .Name  = "Mnemonic::Amu",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Amu},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::At,
            .Name  = "Mnemonic::At",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::At},.Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Prime,
            .Name  = "Mnemonic::Prime",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Prime},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Do,
            .Name  = "Mnemonic::Do",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Do},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::While,
            .Name  = "Mnemonic::While",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::While},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::For,
            .Name  = "Mnemonic::For",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::For},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Until,
            .Name  = "Mnemonic::Until",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Until},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Repeat,
            .Name  = "Mnemonic::Repeat",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Repeat},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Switch,
            .Name  = "Mnemonic::Switch",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Switch},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Case,
            .Name  = "Mnemonic::Case",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Case},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Type,
            .Name  = "Mnemonic::Type",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::Type},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Leaf|Type::Keyword|Type::Operator|Type::Hex,
            .M = Mnemonic::LowHex,
            .Name  = "Mnemonic::LowHex",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::LowHex},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Leaf|Type::Keyword|Type::Operator|Type::Hex,
            .M = Mnemonic::UpHex,
            .Name  = "Mnemonic::UpHex",
            .D = Oper::Noop_,
            .Loc = {.Begin = Lexem::UpHex},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Cosinus,
            .Name  = "Mnemonic::Cosinus",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Cosinus},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Keyword|Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::ArcCosinus,
            .Name  = "Mnemonic::ArcCosinus",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::ArcCosinus},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Keyword|Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Tangent,
            .Name  = "Mnemonic::Tangent",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Tangent},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Keyword|Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::ArcTangent,
            .Name  = "Mnemonic::ArcTangent",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::ArcTangent},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Keyword|Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::Sinus,
            .Name  = "Mnemonic::Sinus",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::Sinus},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Prefix,
            .Sem = Type::Keyword|Type::Unary|Type::Prefix|Type::Operator,
            .M = Mnemonic::ArcSinus,
            .Name  = "Mnemonic::ArcSinus",
            .D = Oper::Unary,
            .Loc = {.Begin = Lexem::ArcSinus},
            .Flags{.V=1}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Object,
            .Name  = "Mnemonic::Object",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Object},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::Static,
            .Name  = "Mnemonic::Static",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::Static},
            .Flags{.V=0}
        },
        {
            .Prim = Type::Keyword,
            .Sem = Type::Keyword,
            .M = Mnemonic::This,
            .Name  = "Mnemonic::This",
            .D = Oper::Identifier,
            .Loc = {.Begin = Lexem::This},
            .Flags{.V=1}
        }
    };


    return Ref.size();
}




size_t ArithmeticLexemes::DeclareTable()
{
    return TokenTable::DeclareTable();
}



TokenTable::TokenTable(Util::Object *Par, const std::string &TableName) : Object(Par, TableName){}

TokenTable::~TokenTable()
{
    Ref.clear();
}

TokenInfo TokenTable::Scan(const char* C)
{
    Book::Debug() << " :" << *C;
    if(Ref.empty())
    {
        AppBook::Warning() << " Tokens reference table is empty";
        return {};
    }

    int unicode = 0;
    if (!*C)
        return {};

    for (auto token : Ref)
    {
        //Book::Debug() << "Token Ref '" << Color::Yellow << token.Name << Color::Reset << ": (" << Color::HotPink4 << token.Loc.Begin << Color::Reset << ") :";
        std::string_view::iterator crs = C;
        std::string_view::iterator rtxt = token.Loc.Begin;
        unicode = 0; // oops...
        //std::size_t sz = std::strlen(rtxt);

        if(*crs != *rtxt) {
            //Book::Debug() << *crs << " <> " << *rtxt;
            continue;
        }
        //Book::Debug() << *crs << " <==> " << *rtxt;
        while ((rtxt && crs) && (*crs && *rtxt) && (*crs == *rtxt))
        {
            if (*crs < 0)
                ++unicode; ///< @note oui/ yes; Soon/Bientôt je supporte quelques symboles UTF-8 (pi, xor,...)

            ++crs;
            ++rtxt;
            //Book::Debug() << *crs << " <==> " << ( rtxt ?  *rtxt : ' ');
        }
        if (!rtxt || (*rtxt == 0))
        {
            if (*crs && !isspace(*crs))
            {
                if ((isalnum(*crs) || (*crs == '_')) && !token.HasType(Type::Operator|Type::Punc))
                    continue;
            }

            token.Loc.Begin = C;
            token.Loc.End = --crs;
            token.Loc.Length = (token.Loc.End - token.Loc.Begin)+1;
            return token;
        }
    }

    Book::Debug() << " No match.";
    return {};
}

TokenTable &TokenTable::operator<<(TokenInfo &NewToken)
{
    Product.emplace_back(NewToken);
    return *this;
}

void TokenTable::DebugDumpRef()
{
    Book::Debug() << " Dump the Tokens Reference Table:";

    for(auto const& Token : Ref)
        Book::Out() << Token.Details();


}



TokenInfo const &TokenTable::ByName(std::string_view MName)
{
    if(Ref.empty())
        throw AppBook::Exception() [Book::Fatal() << " Tokens Table is empty!"];

    for(auto const& Token : Ref)
        if(Token.Name == MName) return Token;

    throw AppBook::Exception() [Book::Fatal() << " Tokens identified by '" << Color::Yellow << MName << Color::Reset << " Is not in this table."];
}

void TokenTable::DebugDumpProduct()
{
    Book::Debug() << " Dump the Tokens Product Table:";

    for(auto const& Token : Product)
        Book::Out() << Token.Details();
}


}