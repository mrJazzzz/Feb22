#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>

class InvalidBar : public std::exception {
public:
	InvalidBar(const char* msg) : exception(msg) {};
};

class WrongDuration : public std::exception {
public:
	WrongDuration(const char* msg) : exception(msg) {};
};
#endif
