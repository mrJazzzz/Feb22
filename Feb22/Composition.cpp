#include "Composition.h"
#include "Exception.h"
using namespace std;

Composition::Composition(): dur_(0){}

void Composition::insert(const Bar& b){
	if (this->dur_ && b.getDuration() != this->dur_)
		throw WrongDuration("Losee.");
	this->comp_.push_back(b);
	if (!this->dur_)
		this->dur_ = b.getDuration();
}

ostream& operator<<(ostream& os, const Composition& c){
	int maxl = 0;
	for (auto& it : c.comp_)
		if (it.maxL() > maxl)
			maxl = it.maxL();
	//cout << maxl;
	for (int i = 1; i <= maxl; i++) {
		string x = "";
		for (auto& it : c.comp_)
			if (it.maxL() >= i)
				x += it.layer(i) +"|";
			else {
				for (int i = 0; i < c.dur_; i++)
					x += "_";
				x += "|";
			}
				
		os << x << endl;
	}
	return os;
}

