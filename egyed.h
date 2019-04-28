#ifndef EGYED_H
#define EGYED_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Egyed{
public:
	vector<string> allel;
	int fitness;
	Egyed(vector<string> v);
	Egyed() {}
	~Egyed();
	void print(int);
};

#endif