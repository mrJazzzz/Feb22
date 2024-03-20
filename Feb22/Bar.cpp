#include "Bar.h"
#include "Symbol.h"
#include "Exception.h"
#include <utility>
using namespace std;



Bar* Bar::copyBar() const{
	Bar* n = new Bar();
	n->elems_ = this->elems_;
	return n;
}

void Bar::insert(const Symbol& x){
	Symbol* s = x.copySymbol();
	int b = s->getStart();
	pair<int, Symbol*> pr = make_pair(b, s);
	this->elems_.insert(pr);
}

int Bar::maxL() const{
	vector<int> num; 
	for (int i = 0; i < this->getDuration(); i++)
		num.push_back(0);
	for (auto& it : this->elems_) 
		for (int i = it.second->getStart(); i < it.second->getEnd(); i++)
			num[i]++;
	int maxl = 0;
	for (auto& it : num)
		if (it > maxl)
			maxl = it;
	return maxl;
}

int Bar::getDuration() const{
	if (this->elems_.size() == 0)
		return 0;
	int b = this->elems_.begin()->second->getStart();
	int e = this->elems_.rbegin()->second->getEnd();
	return e - b;
}

bool Bar::validate(){
	if (this->elems_.size() < 2)
		return true;
	map<int, Symbol*>::iterator it = next(this->elems_.begin());
	for (it; it != this->elems_.end(); it++)
		if (it->second->getStart() > prev(it)->second->getEnd())
			return false;
	return true;
}

void Bar::layerBase(vector<string>& v) const{
	v.clear();
	for (int i = 0; i < this->getDuration(); i++)
		v.push_back("");
	for (auto& it : elems_)
		for (int i = it.second->getStart(); i < it.second->getEnd(); i++)
			v[i] += it.second->getDesc();
	int ml = 0;
	for (auto& it : v)
		if (it.length() > ml)
			ml = it.length();
	for (auto& it : v)
		while (it.length() < ml)
			it += "_";
	/*
	for (auto& it : this->elems_)
		cout << (*it.second) << ";";
	cout << endl;
	
	for (auto& it : v)
		cout << it << " ";
	cout << endl;
	*/
}

string Bar::layer(int l) const{//1 2 3 4
	string s = "";
	vector<string> v;
	this->layerBase(v);
	//cout << "A: "<<v[0] << endl;
	if (l > v[0].length())
		return "";
	for (auto& it : v)
		s += it[l - 1];
	return s;
}



ostream& operator<<(ostream& os, const Bar& b){
	if (!b.copyBar()->validate())
		throw InvalidBar("Losee.");
	for (int i = 1; i <= b.maxL(); i++)
		os << b.layer(i) << "|" << endl;
	return os;
}
