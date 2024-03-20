#ifndef BAR_H
#define BAR_H
#include "Symbol.h"
#include <map>
#include <vector>
#include <iostream>

class Bar {
public:
	Bar() {};
	Bar* copyBar() const;
	void insert(const Symbol& x);
	int getDuration() const;
	bool validate();
	int maxL() const;
	void layerBase(std::vector<std::string>& v) const;
	std::string layer(int l) const;
	friend std::ostream& operator<<(std::ostream& os, const Bar& b);
private:
	std::map<int, Symbol*> elems_;
};
#endif