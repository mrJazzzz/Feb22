#pragma once
#include "Pitch.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

// check if type is defined, forward declarations are not definitions
template <class, class = void>
struct is_defined : std::false_type {};
template <class T>
struct is_defined<
    T, std::enable_if_t<std::is_object<T>::value &&
                        !std::is_pointer<T>::value && (sizeof(T) > 0)>>
    : std::true_type {};

namespace Test1 {

template <class, class = void>
struct is_defined_method : std::false_type {};

template <class Note>
struct is_defined_method<
    Note,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(std::declval<std::ostream &>()
                              << std::declval<const Note &>()),
                     std::ostream &>::value>> : std::true_type {};

template <class Symbol, class Note>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined_method<Note>::value) {
        std::stringstream ss;
        Note n1(Pitch::C, 0, 3);
        ss << n1;
        // cout << s;
        if (ss.str() == "C[0,3]") {

            std::cout << "Test passed" << std::endl;
            return 1;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test1

namespace Test2 {

template <class, class = void>
struct is_defined_method : std::false_type {};

template <class Note>
struct is_defined_method<
    Note,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(std::declval<std::ostream &>()
                              << std::declval<const Note &>()),
                     std::ostream &>::value>> : std::true_type {};

template <class Symbol, class Note>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined_method<Note>::value) {
        std::stringstream ss;
        const Note n1(Pitch::C, 0, 3);
        const Symbol &sym = n1;
        ss << sym;
        // cout << s;
        std::string s = ss.str();
        if (s == "C[0,3]") {
            std::cout << "Test passed" << std::endl;
            return 3;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test2

namespace Test3 {

template <class, class = void>
struct is_defined_method : std::false_type {};

template <class Note>
struct is_defined_method<
    Note,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(std::declval<std::ostream &>()
                              << std::declval<const Note &>()),
                     std::ostream &>::value &&
        std::is_same<decltype(std::declval<Note>() <<= std::declval<int>()),
                     Note &>::value &&
        std::is_same<decltype(std::declval<Note>() >>= std::declval<int>()),
                     Note &>::value>> : std::true_type {};

template <class Symbol, class Note>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined_method<Note>::value) {
        std::stringstream ss;
        Note n1(Pitch::C, 0, 3);
        n1 >>= 1;
        ss << n1;
        n1 <<= 1;
        ss << n1;    
        n1 <<= 17;
        ss << n1;   
        std::string s = ss.str();
        // cout << s;
        if (s == "D[0,3]C[0,3]G[0,3]") {
            std::cout << "Test passed" << std::endl;
            return 4;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test3

namespace Test4 {

template <class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar>
struct is_defined_method<
    Symbol, Note, Pause, Bar,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar>::value) {
        std::stringstream ss;

        Note n1(Pitch::C, 0, 3);
        Note n2(Pitch::A, 3, 4);
        Note n3(Pitch::D, 4, 6);
        Pause p1(6, 7);

        Bar b;
        b.insert(n1);
        b.insert(n2);
        b.insert(n3);
        b.insert(p1);
        ss << b;
         //std::cout << b;
        std::string s = ss.str();
        if (s == "CCCADD_|\n") {
            std::cout << "Test passed" << std::endl;
            return 3;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test4

namespace Test5 {

template <class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar>
struct is_defined_method<
    Symbol, Note, Pause, Bar,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar>::value) {
        std::stringstream ss;

        Note n1(Pitch::C, 0, 3);
        Note n2(Pitch::A, 2, 5);
        Note n3(Pitch::D, 4, 6);
        Pause p1(6, 7);

        Bar b;
        b.insert(n1);
        b.insert(n2);
        b.insert(n3);
        b.insert(p1);

        ss << b;
        // cout << b;
        std::string s = ss.str();
        if (s == "CCCAAD_|\n__A_D__|\n") {
            std::cout << "Test passed" << std::endl;
            return 3;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test5

namespace Test6 {

template <class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar>
struct is_defined_method<
    Symbol, Note, Pause, Bar,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar>::value) {
        std::stringstream ss;

        Note n1(Pitch::C, 0, 3);
        Note n2(Pitch::A, 2, 5);
        Note n3(Pitch::D, 4, 6);
        Pause p1(6, 7);

        Bar b;
        b.insert(p1);
        b.insert(n2);
        b.insert(n1);
        b.insert(n3);
        ss << b;
        std::string s = ss.str();
        if (s == "CCCAAD_|\n__A_D__|\n") {
            std::cout << "Test passed" << std::endl;
            return 3;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test6

namespace Test7 {

template <class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar>
struct is_defined_method<
    Symbol, Note, Pause, Bar,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar, class InvalidBar>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined<InvalidBar>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar>::value) {
        std::stringstream ss;

        Note n1(Pitch::C, 0, 3);
        Note n3(Pitch::D, 5, 6);
        Pause p1(6, 7);

        Bar b;
        b.insert(p1);
        b.insert(n1);
        b.insert(n3);
        try {
            ss << b;
            std::cout << "Test failed" << std::endl;
        } catch (const InvalidBar &e) {
            std::cout << "Test passed" << std::endl;
            return 2;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test7

namespace Test8 {

template <class, class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition>
struct is_defined_method<
    Symbol, Note, Pause, Bar, Composition,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value &&
        std::is_same<decltype(std::declval<Composition>().insert(
                         std::declval<const Bar &>())),
                     void>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar,
                                    Composition>::value) {
        std::stringstream ss;
        Note n1(Pitch::C, 0, 3);
        Note n2(Pitch::A, 3, 4);
        Note n3(Pitch::D, 4, 6);
        Pause p1(6, 7);

        Bar b;
        b.insert(n1);
        b.insert(n2);
        b.insert(n3);
        b.insert(p1);

        Composition c;
        c.insert(b);
        c.insert(b);
        c.insert(b);
        ss << c;
        std::string s = ss.str();
        // cout << s;

        if (s == "CCCADD_|CCCADD_|CCCADD_|\n") {
            std::cout << "Test passed" << std::endl;
            return 5;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test8

namespace Test9 {

template <class, class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition>
struct is_defined_method<
    Symbol, Note, Pause, Bar, Composition,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value &&
        std::is_same<decltype(std::declval<Composition>().insert(
                         std::declval<const Bar &>())),
                     void>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition,
          class WrongDuration>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined<WrongDuration>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar,
                                    Composition>::value) {
        std::stringstream ss;
        Note n1(Pitch::C, 0, 3);
        Note n2(Pitch::A, 3, 4);
        Note n3(Pitch::D, 4, 6);
        Pause p1(6, 7);

        Bar b;
        b.insert(n1);
        b.insert(n2);
        b.insert(n3);
        b.insert(p1);

        Composition c;

        Bar b2;
        c.insert(b);

        b2.insert(n1);
        try {
            c.insert(b2);
            std::cout << "Test failed" << std::endl;
        } catch (const WrongDuration &e) {
            std::cout << "Test passed" << std::endl;
            return 1;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test9

namespace Test10 {

template <class, class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition>
struct is_defined_method<
    Symbol, Note, Pause, Bar, Composition,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value &&
        std::is_same<decltype(std::declval<Composition>().insert(
                         std::declval<const Bar &>())),
                     void>::value &&
        std::is_same<decltype(std::declval<std::ostream &>()
                              << std::declval<const Composition &>()),
                     std::ostream &>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar,
                                    Composition>::value) {
        std::stringstream ss;
        // CCCAAD_|
        // __A_D__|
        Note n1(Pitch::C, 0, 3);
        Note n2(Pitch::A, 2, 5);
        Note n3(Pitch::D, 4, 6);
        Pause p1(6, 7);
        // Note n1(C, 0, 2);

        Bar b;
        b.insert(p1);
        b.insert(n3);
        b.insert(n1);
        b.insert(n2);

        // cout << b << endl << endl;

        Composition c;
        c.insert(b);
        c.insert(b);
        c.insert(b);
       
        ss << c;
        std::string s = ss.str();
        // std::cout << s;
        if (s == "CCCAAD_|CCCAAD_|CCCAAD_|\n"
                 "__A_D__|__A_D__|__A_D__|\n") {
            std::cout << "Test passed" << std::endl;
            return 5;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test10

namespace Test11 {

template <class, class, class, class, class, class = void>
struct is_defined_method : std::false_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition>
struct is_defined_method<
    Symbol, Note, Pause, Bar, Composition,
    std::enable_if_t<
        std::is_same<decltype(Note(std::declval<Pitch>(), std::declval<int>(),
                                   std::declval<int>())),
                     Note>::value &&
        std::is_same<decltype(Pause(std::declval<int>(), std::declval<int>())),
                     Pause>::value &&
        std::is_same<decltype(std::declval<Bar>().insert(
                         std::declval<const Symbol &>())),
                     void>::value &&
        std::is_same<decltype(std::declval<Composition>().insert(
                         std::declval<const Bar &>())),
                     void>::value &&
        std::is_same<decltype(std::declval<std::ostream &>()
                              << std::declval<const Composition &>()),
                     std::ostream &>::value>> : std::true_type {};

template <class Symbol, class Note, class Pause, class Bar, class Composition>
int tst() {
    if constexpr (is_defined<Symbol>::value && is_defined<Note>::value &&
                  is_defined<Pause>::value && is_defined<Bar>::value &&
                  is_defined_method<Symbol, Note, Pause, Bar,
                                    Composition>::value) {
        std::stringstream ss;
        // CCCAAD_|
        // __A_D__|
        Note n1(Pitch::C, 0, 3);
        Note n2(Pitch::A, 2, 5);
        Note n3(Pitch::D, 4, 6);
        Pause p1(6, 7);

        Bar b1;
        b1.insert(p1);
        b1.insert(n3);
        b1.insert(n1);
        b1.insert(n2);

        // CCCAAD_|
        // __AAA__|
        // __A_D__|
        Bar b2;
        b2.insert(p1);
        b2.insert(n3);
        b2.insert(n1);
        b2.insert(n2);

        b2.insert(n2);

        Composition c;
        c.insert(b1);
        c.insert(b2);
        c.insert(b1);
        // std::cout << b2;

        ss << c;
        std::string s = ss.str();
         std::cout << s;
        if (s == "CCCAAD_|CCCAAD_|CCCAAD_|\n"
                 "__A_D__|__AAA__|__A_D__|\n"
                 "_______|__A_D__|_______|\n") {
            std::cout << "Test passed" << std::endl;
            return 5;
        } else {
            std::cout << "Test failed" << std::endl;
        }
    } else {
        std::cout << "Interface failed" << std::endl;
    }
    return 0;
}
} // namespace Test11
