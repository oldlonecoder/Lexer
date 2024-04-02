//
// Created by oldlonecoder on 24-03-12.
//

#include "Test.h"

namespace lex
{
Test::Test(const std::string &AppID, int argc, char** argv): Book::ApplicationBase(AppID, argc, argv) {}

//Test::~Test()
//{
//
//}

Book::Result Test::Run()
{
    Setup();

    lex::TokenTable Tokens;

    lex::Lexer Lex;
    Lex.Config()={
        .Text = "BebeSpi = 65768+4-1;",
        .Production = &Tokens
    };

    try {
        auto R = Lex.Execute();
        auto [Ic, A] = Book::Enums::CodeAttributes(R);

        Book::Status() << " Lexer return : " << A << Ic << Book::Enums::CodeText(R) << Color::Reset << " -> ";
        Tokens.DebugDumpProduct();
    }
    catch(AppBook::Exception& E)
    {
        std::cerr << E.what() << std::endl; // Yep, `<< std::endl` is faster than `<< '\n'` !!!
    }
    catch(std::exception& E)
    {
        std::cerr << E.what() << std::endl; // Yep, `<< std::endl` is faster than `<< '\n'` !!!
    }

    return Book::Result::Ok;
}

Book::Result Test::Setup()
{
    ApplicationBase::Setup();

    AppBook::CreateSection("Lexer-Test").Open().CreateSectionContents("DevJournal");
    Book::Select()["Lexer-Test"]["DevJournal"];
    Book::Debug() << " Lexer tests are ready to begin...";

    return Book::Result::Ok;
}



} // lex




auto main(int argc, char **argv) -> int
{
    lex::Test Tests = lex::Test("Lexer-API", argc,argv);

    Tests.Run();
    std::cout << "Duh! Refaire les tests!" << std::endl;

    return 0;
}

