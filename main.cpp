#include "feladat.h"
#include "egyed.h"
#include "teszt.h"
#include <stdlib.h>
#include <time.h> 

#define POPMERET 40
#define ELIT 25

//cout << endl<< poz("name", "Joshua", e, feladat); VEKTORBELI POZÍVIÓT ADJA MEG
int poz(string tulajdonsag, string ertek, Egyed e, Feladat f) {
	int sz = -1;
	for (unsigned int i = 0; i < f.tul.size(); i++) {
		if (f.tul[i] == tulajdonsag) {
			for (unsigned int j = f.oszlop*i; j < f.oszlop*(i + 1); j++) {
				if (e.allel[j] == ertek) {
					sz = j;
				}
			}
		}
	}
	return sz;
}

int fitness(Egyed e, Feladat f) {
	Teszt test;
	int fit = 0; //fitness értéket beállító számláló
	int i = 0; //számlálója a teszt vektornak
	while (i < test.kikotes.size()) {
		if (test.kikotes[i] == "O") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f);
			int szamlalo = 0;
			for (int j = 0; j < f.sor; j++) {
				if (a == j * f.oszlop) { szamlalo++; }
				if (a == j * f.oszlop + f.oszlop - 1) { szamlalo++; }
			}
			if (szamlalo != 1) { fit++; }

			i += 3;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "P") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f);
			int b = stoi(test.kikotes[i + 3]) - 1;
			if (a%f.oszlop != b) { fit++; }

			i += 4;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "B") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f) % f.oszlop;
			int b = poz(test.kikotes[i + 3], test.kikotes[i + 4], e, f) % f.oszlop;
			int c = poz(test.kikotes[i + 5], test.kikotes[i + 6], e, f) % f.oszlop;
			if (!((a > b && a < c) || (a < b && a > c))) { fit++; }

			i += 7;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "L") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f) % f.oszlop;
			int b = poz(test.kikotes[i + 3], test.kikotes[i + 4], e, f) % f.oszlop;
			if (a != b) { fit++; }

			i += 5;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "N") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f) % f.oszlop;
			int b = poz(test.kikotes[i + 3], test.kikotes[i + 4], e, f) % f.oszlop;
			if (!((a == (b - 1)) || (a == (b + 1)))) { fit++; }

			i += 5;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "EL") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f) % f.oszlop;
			int b = poz(test.kikotes[i + 3], test.kikotes[i + 4], e, f) % f.oszlop;
			if (a != (b - 1)) { fit++; }

			i += 5;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "ER") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f) % f.oszlop;
			int b = poz(test.kikotes[i + 3], test.kikotes[i + 4], e, f) % f.oszlop;
			if (a != (b + 1)) { fit++; }

			i += 5;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "SL") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f) % f.oszlop;
			int b = poz(test.kikotes[i + 3], test.kikotes[i + 4], e, f) % f.oszlop;
			if (a >= b) { fit++; }

			i += 5;
			if (i >= test.kikotes.size()) { break; }
		}
		if (test.kikotes[i] == "SR") {
			int a = poz(test.kikotes[i + 1], test.kikotes[i + 2], e, f) % f.oszlop;
			int b = poz(test.kikotes[i + 3], test.kikotes[i + 4], e, f) % f.oszlop;
			if (a <= b) { fit++; }

			i += 5;
			if (i >= test.kikotes.size()) { break; }
		}
	}
	return fit;
}

Egyed keresztez(Egyed e1, Egyed e2,Feladat f){ 
	Egyed uj = e1;

	unsigned int v = rand() % f.oszlop;//v=vágási pont
	v = v*f.oszlop;
	for (unsigned int i = 0; i < v; i++) {
		uj.allel[i] = e2.allel[i];
	}
	uj.fitness = fitness(uj, f);
	return uj;
}

Egyed mutal(Egyed e, Feladat f) {
	Egyed uj(e.allel);
	unsigned int hely = rand() % f.tul.size();
	unsigned int poz1 = hely*f.oszlop+rand() % f.oszlop;
	unsigned int poz2 = hely * f.oszlop + rand() % f.oszlop;
	string csere = uj.allel[poz1];
	uj.allel[poz1] = uj.allel[poz2];
	uj.allel[poz2] = csere;
	uj.fitness = fitness(uj, f);
	return uj;
}

Egyed mutal2(Egyed e, Feladat f) {
	Egyed uj(e.allel);
	for (unsigned int i = 0; i < f.sor; i++) {
		unsigned int p1 = i*f.oszlop+ (rand() % f.oszlop);
		unsigned int p2 = i*f.oszlop + (rand() % f.oszlop);
		string csere = uj.allel[p1];
		uj.allel[p1] = uj.allel[p2];
		uj.allel[p2] = csere;
	}
	uj.fitness=fitness(uj, f);
	return uj;
}

void rendezes(Egyed populacio[], int meret) {
	Egyed X;
	int i, j;
	for (i = 1; i < meret; i++) {
		X = populacio[i];
		j = i - 1;
		while ((j >= 0) && (populacio[j].fitness > X.fitness)) {
			populacio[j + 1] = populacio[j];
			j = j - 1;
		}
		populacio[j + 1] = X;
	}
}


int main() {	
	Feladat feladat("feladat.txt");
	Egyed egyed(feladat.allel);
	//egyed.fitness = fitness(egyed, feladat);
	//egyed.print(feladat.oszlop);

	// Kezdeti populacio inicializalasa
	Egyed populacio[POPMERET];
	for (unsigned int i = 0; i < POPMERET; i++) {
		populacio[i]=mutal2(egyed, feladat);
	}
	srand(time(NULL));

	Egyed temp[POPMERET * 4];
	unsigned int generacio = 0;
	bool siker = false;
	while (!siker) {
		unsigned int k = 0;
		generacio++;
		cout << endl <<"Generation " << generacio << ":";
		// Masoljunk at minden eddigit	
		for (unsigned int i = 0; i < POPMERET; i++) {
			temp[k] = populacio[i];
			k++;
		}
		// Mutálás	
		for (unsigned int i = 0; i < POPMERET; i++) {
			temp[k] = mutal(populacio[i],feladat);
			k++;
		}
		// Keresztezés		
		for (unsigned int i = 0; i < POPMERET; i++) {
			
			int a = rand() % POPMERET;
			int b = rand() % POPMERET;
			Egyed e1 = populacio[a];
			Egyed e2 = populacio[b];
			temp[k] = keresztez(e1, e2, feladat);
			k++;
		}
		// Keresztezés a mutalt egyedeken		
		for (unsigned int i = 0; i < POPMERET; i++) {
			Egyed e1 = mutal(populacio[rand() % POPMERET],feladat);
			temp[k] = keresztez(mutal(populacio[rand() % POPMERET], feladat), mutal(populacio[rand() % POPMERET], feladat),feladat);
			k++;
		}
		// Valasszuk ki, kik maradnak
		rendezes(temp, 4 * POPMERET);
		for (unsigned int i = 0; i < ELIT; i++) {
			populacio[i] = temp[i];
		}
		for (unsigned int i = ELIT; i < POPMERET; i++) {
			populacio[i] = temp[rand() % (POPMERET*4-ELIT)+ELIT];
		}
		populacio[0].print(feladat.oszlop);
		siker = (populacio[0].fitness == 0);
	}	
	getchar();
}

