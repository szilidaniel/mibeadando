#ifndef TESZT_H
#define TESZT_H

#include <string>
#include <vector>

using namespace std;

class Teszt{
public:
	vector<string> kikotes;
	Teszt();
	~Teszt();
	void hozzafuz(string);
	void print();
};

#endif