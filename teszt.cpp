#include "teszt.h"
#include <iostream>
#include <fstream>


Teszt::Teszt(){
	ifstream myfile;
	myfile.open("kikotesek.txt");
	if (!myfile.fail())
	{
		while (!myfile.eof()) {
			string a;
			myfile >> a;
			this->hozzafuz(a);
		}
		myfile.close();
	}
	else { cerr << "Hianyzo fajl!"; }
}

Teszt::~Teszt()
{
}


void Teszt::hozzafuz(string s) {
	this->kikotes.push_back(s);
}

void Teszt::print() {
	cout << endl<< "---------------------" << endl;
	for (unsigned int i = 0; i < this->kikotes.size(); i++) {
		cout << this->kikotes[i] << "\t";
	}
	cout << endl<< "---------------------" << endl;
}