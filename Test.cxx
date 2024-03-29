//
// Created by oldlonecoder on 24-03-12.
//

#include "Test.h"

namespace lex
{
Test::Test(const std::string &AppID, int argc, char** argv): Book::ApplicationSkel(AppID, argc, argv) {}

Test::~Test()
{

}

Book::Result Test::Run()
{
    Setup();



    return Book::Result::Ok;
}

Book::Result Test::Setup()
{
    ApplicationSkel::Setup();

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

