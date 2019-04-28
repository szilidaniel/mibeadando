#include "egyed.h"

Egyed::Egyed(vector<string> v){
	this->allel = v;
}


Egyed::~Egyed(){
	
}

void Egyed::print(int oszlop) {
	for (unsigned int i = 0; i < this->allel.size(); i++) {
		if ((i%oszlop) == 0) { cout << endl; }
		cout << this->allel[i] << "\t";
	}
	cout << endl << "Fitness: " << this->fitness << endl;
}
