#include "Symbol.h"
using namespace std;

int Symbol::getStart(){
	return this->start_;
}
int Symbol::getEnd(){
	return this->end_;
}
int Symbol::getDuration(){
	return this->end_-this->start_;
}
std::string Symbol::getDesc(){
	return this->desc_;
}
Symbol* Symbol::copySymbol() const{
	return new Symbol(this->start_,this->end_);
}
bool Symbol::operator<(const Symbol& other){
	return this->start_ < other.start_ ? true : false;
}
ostream& operator<<(ostream& os, const Symbol& x){
	os << x.desc_ << "[" << to_string(x.start_) << "," << to_string(x.end_) << "]";
	return os;
}

Note::Note(Pitch h, const int& s, const int& e): Symbol(s, e) {
	this->desc_ = this->pitchToDesc(h);
	this->p_ = h;
}
Note* Note::copySymbol() const{
	return new Note(this->p_, this->start_, this->end_);
}
Note& Note::operator<<=(int x)
{
	int t = this->pitchToNum(this->p_);
	t -= x % 7;
	while (t < 0) t += 7;
	t %= 7;
	this->p_ = this->numToPitch(t);
	this->desc_ = this->pitchToDesc(this->p_);
	return *this;
}
Note& Note::operator>>=(int x){
	int t = this->pitchToNum(this->p_);
	t += x%7;
	while (t < 0) t += 7;
	t %= 7;
	this->p_ = this->numToPitch(t);
	this->desc_ = this->pitchToDesc(this->p_);
	return *this;
}
int Note::pitchToNum(Pitch p)
{
	switch (p) {
		case C:
			return 0;
		case D:
			return 1;
		case E:
			return 2;
		case F:
			return 3;
		case G:
			return 4;
		case A:
			return 5;
		case B:
			return 6;
	}
}
Pitch Note::numToPitch(int x){
	int t = x % 7;
	switch (t) {
		case 0:
			return C;
		case 1:
			return D;
		case 2:
			return E;
		case 3:
			return F;
		case 4:
			return G;
		case 5:
			return A;
		case 6:
			return B;
	}
}
string Note::pitchToDesc(Pitch x){
	switch (x) {
		case C:
			return "C";
		case D:
			return "D";
		case E:
			return "E";
		case F:
			return "F";
		case G:
			return "G";
		case A:
			return "A";
		case B:
			return "B";
	}
}


Pause::Pause(const int& s, const int& e):Symbol(s,e){
	this->desc_ = "_";
}
Pause* Pause::copySymbol() const{
	return new Pause(this->start_, this->end_);
}
