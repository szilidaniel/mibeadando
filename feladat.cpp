#include "feladat.h"

Feladat::Feladat() {}
Feladat::Feladat(const string& file) {
	ifstream myfile;
	myfile.open(file);
	if (!myfile.fail())
	{
		myfile >> this->oszlop;
		myfile >> this->sor;
		for (unsigned int s = 0; (s < this->sor) && (!myfile.eof()); s++) {
			string a;
			myfile >> a;
			this->tul.push_back(a);
			for (unsigned int o = 0; (o < this->oszlop) && (!myfile.eof()); o++) {
				string b;
				myfile >> b;
				this->allel.push_back(b);
			}
		}
		myfile.close();
	}
	else { cerr << "Hianyzo fajl!"; }
}
void Feladat::print() {
	cout << this->oszlop << endl;
	cout << this->sor << endl;
	cout << "---------------------" << endl;
	for (unsigned int i = 0; i < this->tul.size(); i++) {
		cout << this->tul[i] << endl;
	}
	cout << "---------------------" << endl;
	for (unsigned int i = 0; i < this->allel.size(); i++) {
		if ((i%this->oszlop) == 0) { cout << endl; }
		cout << this->allel[i] << "\t";
		
	}
}
