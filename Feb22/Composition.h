#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "Bar.h"
#include <vector>
#include <iostream>

class Composition{
public:
	Composition();
	void insert(const Bar& b);
	friend std::ostream& operator<<(std::ostream& os, const Composition& c);
private:
	int dur_;
	std::vector<Bar> comp_;
};

#endif
