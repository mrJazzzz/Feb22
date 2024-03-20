// <- ovde idu include-ovi implementiranih klasa
#include "Pitch.h"
#include "Symbol.h"
#include "Bar.h"
#include "Composition.h"
#include "tst.h"
#include "Exception.h"
#include <iostream>
using namespace std;

// forward declare tested types
class Symbol;
class Note;
class Pause;
class Bar;
class Composition;

class InvalidBar;
class WrongDuration;

int main(int argc, char const *argv[]) {
    using namespace std;
    int pts = 0;
    pts += Test1::tst<Symbol, Note>(); // ispis
    pts += Test2::tst<Symbol, Note>(); // const poly ispis
    pts += Test3::tst<Symbol, Note>(); // operator za shift sa modovanjem
    pts += Test4::tst<Symbol, Note, Pause, Bar>(); // insert
    pts += Test5::tst<Symbol, Note, Pause, Bar>(); // insert with height
    pts += Test6::tst<Symbol, Note, Pause, Bar>(); // insert with height, sort
    pts += Test7::tst<Symbol, Note, Pause, Bar,
                      InvalidBar>(); // invalidan bar test exception na ispisu
    pts += Test8::tst<Symbol, Note, Pause, Bar,
                      Composition>(); // insert composition && print
    pts += Test9::tst<Symbol, Note, Pause, Bar, Composition,
                      WrongDuration>(); // composition insert except
    pts += Test10::tst<Symbol, Note, Pause, Bar,
                       Composition>(); // comp print height
    pts += Test11::tst<Symbol, Note, Pause, Bar,
                       Composition>(); // comp print height 3

    std::cout << "Points: " << pts << std::endl;
    
    return 0;
}
