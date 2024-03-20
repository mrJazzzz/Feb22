#pragma once
#include "Pitch.h"
#include <string>
#include <iostream>
class Symbol{
public:
	Symbol(const int& s, const int& e):start_(s), end_(e){};
	int getStart();
	int getEnd();
	int getDuration();
	std::string getDesc();
	virtual Symbol* copySymbol() const;
	friend std::ostream& operator<<(std::ostream& os, const Symbol& x);
	bool operator<(const Symbol& other);
protected:
	int start_;
	int end_;
	std::string desc_;
};

class Note : public Symbol {
public:
	Note(Pitch h, const int& s, const int& e);
	virtual Note* copySymbol() const override;
	Note& operator<<=(int x);
	Note& operator>>=(int x);
private:
	int pitchToNum(Pitch p);
	Pitch numToPitch(int x);
	std::string pitchToDesc(Pitch x);
	Pitch p_;
};



class Pause :public Symbol {
public:
	Pause(const int& s, const int& e);
	virtual Pause* copySymbol() const override;
};