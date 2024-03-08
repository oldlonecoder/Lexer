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
 ******************************************************************************************/

#pragma once


#include "M-Lexer/Interface.h"
#include <AppBook/Util/StrAcc.h>
#include <map>

namespace MLex
{


namespace Type
{
    using T = uint64_t;
    constexpr T Number      = 0x000000000001;
    constexpr T Text        = 0x000000000002;
    constexpr T VoidPtr     = 0x000000000004;
    constexpr T Any         = 0x000000000008;
    constexpr T Leaf        = 0x000000000010;
    constexpr T Sign        = 0x000000000020;
    constexpr T I8          = 0x000000000040;
    constexpr T I16         = 0x000000000080;                                                                              // 0x7F41
    constexpr T I32         = 0x000000000100;
    constexpr T I64         = 0x000000000200;
    constexpr T U8          = 0x000000000400;
    constexpr T U16         = 0x000000000800;
    constexpr T U32         = 0x000000001000;
    constexpr T U64         = 0x000000002000;
    constexpr T Float       = 0x000000004000;                                                                              // real: f32, f64, f128... ^^
    constexpr T Var         = 0x000000008000;                                                                              // Ne pas oublier d'ajouter ce type a toutes "variables"
    constexpr T Bloc        = 0x000000010000;
    constexpr T Pipe        = 0x000000020000;
    constexpr T Keyword     = 0x000000040000;
    constexpr T Unary       = 0x000000080000;
    constexpr T Prefix      = 0x000000100000;
    constexpr T Postfix     = 0x000000200000;
    constexpr T Operator    = 0x000000400000;
    constexpr T Binary      = 0x000000800000;
    constexpr T Function    = 0x000001000000;
    constexpr T FunctionPtr = 0x000002000000;
    constexpr T Object      = 0x000004000000;
    constexpr T Pointer     = 0x000008000000;
    constexpr T Type        = 0x000010000000;
    constexpr T Id          = 0x000020000000;
    constexpr T Ref         = 0x000040000000;
    constexpr T Punc        = 0x000080000000;
    constexpr T Assign      = 0x000100000000;
    constexpr T Bool        = 0x000200000000;
    constexpr T Hex         = 0x000400000000;
    constexpr T OpenPair    = 0x000800000000;
    constexpr T ClosePair   = 0x001000000000;
    constexpr T Const       = 0x002000000000;
    constexpr T Static      = 0x008000000000;                                                                              ///< Flag set at the parser phase when applicable.
    constexpr T F32         = 0x010000000000;
    constexpr T F64         = 0x020000000000;
    constexpr T F128        = 0x040000000000;
    constexpr T OctalFormat = 0x080000000000;
    constexpr T BinFormat   = 0x100000000000;
    constexpr T LineComment = 0x200000000000;
    constexpr T BlocComment = 0x400000000000;
    constexpr T Litteral    = 0x800000000000;                                                                              ///< Litteral types { number, string/Text };
    constexpr T Null        = 0x1000000000000000;
    constexpr T Integer     = Type::I8 | Type::I16 | Type::I32 | Type::I64 | Type::U8 | Type::U16 | Type::U32 | Type::U64;
    constexpr T Unsigned    = Type::U8 | Type::U16 | Type::U32 | Type::U64;
}


namespace Mnemonic
{
    using T = uint16_t;
    constexpr T Null = 0;
    constexpr T LeftShift=0;
    constexpr T Radical=0;
    constexpr T Exponent=0;
    constexpr T RightShift=0;
    constexpr T Decr=0;
    constexpr T Incr=0;
    constexpr T AssignAdd=0;
    constexpr T AssignSub=0;
    constexpr T AssignMul=0;
    constexpr T AssignDiv=0;
    constexpr T AssignMod=0;
    constexpr T AssignAnd=0;
    constexpr T AssignOr=0;
    constexpr T AssignXor=0;
    constexpr T AssignC1=0;
    constexpr T AssignLeftShift=0;
    constexpr T AssignRightShift=0;
    constexpr T Deref=0;
    constexpr T LessEq=0;
    constexpr T GreaterEq=0;
    constexpr T Equal=0;
    constexpr T NotEqual=0;  // != <>
    constexpr T Add=0;
    constexpr T Sub=0;
    constexpr T Mul=0;
    constexpr T Indirection=0;
    constexpr T CommentCpp=0;
    constexpr T Modulo=0;
    constexpr T LessThan=0;
    constexpr T GreaterThan=0;
    constexpr T Assign=0;
    constexpr T BinaryAnd=0;
    constexpr T BinaryOr=0;
    constexpr T BinaryXor=0;
    constexpr T C1=0;           // complement a 1
    constexpr T C2=0;
    constexpr T BinaryNot=0;          //
    constexpr T LogicalAnd=0;
    constexpr T LogicalOr=0;
    constexpr T OpenAbsOp=0;
    constexpr T CloseAbsOp=0;
    constexpr T OpenPar=0;
    constexpr T ClosePar=0;
    constexpr T Openindex=0;
    constexpr T Closeindex=0;
    constexpr T Openbrace=0;
    constexpr T Closebrace=0;
    constexpr T BeginComment=0;
    constexpr T EndComment=0;
    constexpr T Div=0;
    constexpr T Comma=0;
    constexpr T Scope=0;
    constexpr T Semicolon=0;
    constexpr T Colon=0;
    constexpr T Range=0;
    constexpr T Factorial=0;
    constexpr T Positive=0;
    constexpr T Negative=0;
    constexpr T Squote=0; // '
    constexpr T Dquote=0; // "
    constexpr T Ternary=0; // ? :
    constexpr T Hash=0; // #
    constexpr T Eos=0;
    constexpr T Dot=0;
    constexpr T Return=0;
    constexpr T If=0;
    constexpr T Pi=0;
    constexpr T Number=0;
    constexpr T U8=0;
    constexpr T U16=0;
    constexpr T U32=0;
    constexpr T U64=0;
    constexpr T I8=0;
    constexpr T I16=0;
    constexpr T I32=0;
    constexpr T I64=0;
    constexpr T Float=0;
    constexpr T String=0;
    constexpr T Then=0;
    constexpr T Else=0;
    constexpr T Const=0;
    constexpr T Include=0;
    constexpr T Amu=0;
    constexpr T At=0;
    constexpr T Prime=0;
    constexpr T Do=0;
    constexpr T While=0;
    constexpr T For=0;
    constexpr T Until=0;
    constexpr T Repeat=0;
    constexpr T Switch=0;
    constexpr T Case=0;
    constexpr T Type=0;
    constexpr T LowHex=0;
    constexpr T UpHex=0;
    constexpr T Cosinus=0;
    constexpr T ArcCosinus=0;
    constexpr T Tangent=0;
    constexpr T ArcTangent=0;
    constexpr T Sinus=0;
    constexpr T ArcSinus=0;
    constexpr T Object=0;
    constexpr T Static=0;
    constexpr T This=0;
    constexpr T Unshadow=0;
    constexpr T Catch=0;
    constexpr T Throw=0;
    constexpr T Try=0;
    constexpr T Noop=0;
    constexpr T LineComment=0;
    constexpr T BlocComment = 0;
};


namespace Lexem
{

using T = const char*;//std::string_view;
constexpr T Null          = "null";
constexpr T LeftShift     = "<<";
constexpr T Radical       = "^/";
constexpr T Exponent      = "^";
constexpr T RightShift    = ">>";
constexpr T Decr          = "--";
constexpr T Incr          = "++";
constexpr T AssignAdd     = "+=";
constexpr T AssignSub     = "-=";
constexpr T AssignMul     = "*=";
constexpr T AssignDiv     = "/=";
constexpr T AssignMod     = "%=";
constexpr T AssignAnd     = "&=";
constexpr T AssignOr      = "|=";
constexpr T AssignXor     = "><=";
constexpr T AssignC1      = "`="; // Insérer AssignCompletment à 2 =>  { ``=  }
constexpr T AssignLShift  = "<<=";
constexpr T AssignRShift  = ">>=";
constexpr T Deref         = "->";
constexpr T LessEqual     = "<=";
constexpr T GreaterEqual  = ">=";
constexpr T Equal         = "==";
constexpr T NotEqual      = "!=";  // != <>
constexpr T Addition      = "+";
constexpr T Sub           = "-";
constexpr T Multiply      = "*";
constexpr T Indirection   = "*";
constexpr T CommentCpp    = "//";
constexpr T Modulo        = "%";
constexpr T Xor           = "><";
constexpr T LessThan      = "<";
constexpr T GreaterThan   = ">";
constexpr T Assign        = "=";
constexpr T BinaryAnd     = "&";
constexpr T BinaryOr      = "|";
constexpr T C1            = "`"; ///< compl&eacute;ment &agrave; 1
constexpr T C2            = "``";///< compl&eacute;ment &agrave; 2
constexpr T Not           = "!";
constexpr T BoolAnd       = "&&";
constexpr T BoolOr        = "||";
constexpr T AbsBegin      = "|<";// |< absolute value expr >|
constexpr T AbsEnd        = ">|";
constexpr T OpenPar       = "(";
constexpr T ClosePar      = ")";
constexpr T OpenIndex     = "[";
constexpr T CloseIndex    = "]";
constexpr T BraceBegin    = "{";
constexpr T BraceEnd      = "}";
constexpr T CommentBegin  = "/*";
constexpr T CommentEnd    = "*/";
constexpr T Division      = "/";
constexpr T Comma         = ",";
constexpr T Scope         = "::";
constexpr T Semicolon     = ";";
constexpr T Colon         = ":";
constexpr T Range         = "..";
constexpr T Factorial     = "!";
constexpr T Positive      = "+";
constexpr T Negative      = "-";
constexpr T Squote        = "'";  // '
constexpr T Dquote        = "\""; // "
constexpr T Ternary       = "?";  // ? :
constexpr T Hash          = "#";  // #
constexpr T Eos           = "$";
constexpr T Dot           = ".";
constexpr T Return        = "return";
constexpr T If            = "if";
constexpr T Pi            = "pi";
constexpr T Number        = "number";
constexpr T U8            = "u8";
constexpr T U16           = "u16";
constexpr T U32           = "u32";
constexpr T U64           = "u64";
constexpr T I8            = "i8";
constexpr T I16           = "i16";
constexpr T I32           = "i32";
constexpr T I64           = "i64";
constexpr T Float         = "real";
constexpr T String        = "string";
constexpr T Then          = "then";
constexpr T Else          = "else";
constexpr T Const         = "const";
constexpr T Include       = "include";
constexpr T Amu           = "amu";
constexpr T At            = "@";
constexpr T Prime         = "`"; ///@todo change...
constexpr T Do            = "do";
constexpr T While         = "while";
constexpr T For           = "for";
constexpr T Until         = "until";
constexpr T Repeat        = "repeat";
constexpr T Switch        = "switch";
constexpr T Case          = "case";
constexpr T Type          = "type";
constexpr T LowHex        = "0x";
constexpr T UpHex         = "0X";
constexpr T Cosinus       = "cos";
constexpr T ArcCosinus    = "acos";
constexpr T Tangent       = "tan";// tan(4*a*m)  - sin(4ac) sina
constexpr T ArcTangent    = "atan";
constexpr T Sinus         = "sin";
constexpr T ArcSinus      = "asin";
constexpr T Object        = "object";
constexpr T Static        = "static";
constexpr T This          = "me";
constexpr T Unshadow      = ".::"; // If a local variable shadows a higher scoped variable, then this operator will address the variable from within the first bloc where the given variable is scoped.
constexpr T Catch         = "catch";
constexpr T Throw         = "throw";
constexpr T Try           = "try";
constexpr T LineComment   = "//";
constexpr T BlocComment   = "/*";


} // namespace MLex


namespace Oper
{
using T = uint8_t;
constexpr T Scope      = 0;
constexpr T Assign_rhs = 1; //  A = B = ER!
constexpr T Deref      = 2;
constexpr T Prefix     = 3;
constexpr T Postfix    = 3;
constexpr T Unary      = 3;
constexpr T Paranthese = 5;
constexpr T Exponent   = 6;
constexpr T Bits       = 7;
constexpr T Product    = 8;
constexpr T Addition   = 9;
constexpr T Shift      = 10;
constexpr T Equality   = 11;
constexpr T Comp       = 12;
constexpr T Bool_and   = 13;
constexpr T Bool_xor   = 14;
constexpr T Bool_or    = 15;
constexpr T Boolean    = 16;
constexpr T Ternary    = 17;
constexpr T Comma      = 18;
constexpr T Identifier = 19;
constexpr T Assign     = 20; // a + b * m = 0 - 1 ( assign is right hand side association so the operator has lowest priority)
constexpr T Noop_      = 21;

}

struct ULEXER_API Component
{

    static std::map<Lexical::Type::T,     std::string_view> TypeEnums;
    static std::map<Lexical::Mnemonic::T, std::string_view> MnemonicEnums;

    static std::string  Name(Type::T Typ);
    static Type::T      FromStr(const std::string& TName);
    static std::string  MnemonicName(Mnemonic::T M);
    static Mnemonic::T     MnemonicEnum(const std::string& MName);
};

} // namespace MLex


