#ifndef FELADAT_H
#define DELADAT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Feladat {
public:
	unsigned int oszlop;
	unsigned int sor;
	vector<string> tul;
	vector<string> allel;
	Feladat();
	Feladat(const string& file);
	void print();
};
#endif // !FELADAT_H