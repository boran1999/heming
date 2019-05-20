#pragma once
#include<iostream>
#include<fstream>
#include "functions.h"

using namespace std;

class Heming
{
public:
	Heming(const char* filename, const char* filename2);
	void blocks(const char* filename);
	void unblocks(const char* filename, const char* filename1);
protected:
	ifstream in;
	ofstream out;
	int N;
	int *mas = new int[8];
	int *splitmas = new int[8];
	char a;
};

Heming::Heming(const char* filename, const char* filename2)
{
	N = get_amount_simbols(filename);
	in.open(filename, ios_base::binary);
	out.open(filename2);

}

void Heming::blocks(const char* filename) {
	ofstream outn(filename);
	char block[10];
	int number = 0;
	int kol;
	if (N % 4 == 0)
		kol = N / 4;
	else
		kol = N / 4 + 1;
	for (int i = 0; i < kol - 1; i++) {
		block[0] = '&'; outn << block[0];
		block[1] = '&'; outn << block[1];
		outn << kol << i + 1;
		for (int j = 0; j < 4; j++) {
			in.get(a);
			block[j + 2] = a;
		}
		block[6] = '$';
		block[7] = '$';
		for (int k = 2; k < 8; k++) {
			outn << block[k];
		}
	}
	block[0] = '&'; outn << block[0];
	block[1] = '&'; outn << block[1];
	outn << kol << kol;
	int index = 4 * (kol - 1);
	for (int j = 0; j < N - index; j++) {
		in.get(a);
		block[j + 2] = a;
	}
	index = N - index;
	block[index + 2] = '$';
	block[index + 3] = '$';
	for (int k = 2; k < index + 4; k++) {
		outn << block[k];
	}
	outn.close();
}

void Heming::unblocks(const char* filename, const char* filename1) {
	ifstream inn(filename, ios_base::binary);
	ofstream outm(filename1);
	N = get_amount_simbols(filename);
	char *unbl = new char[N];
	while (N / 10 > 0) {
		for (int i = 0; i < 10; i++) {
			inn.get(unbl[i]);
			if (i % 10 > 3 && i % 10 <= 7)


				outm << unbl[i];
		}
		N -= 10;
	}
	int ost = N-6;
	for (int i = 0; i < N; i++) {
		inn.get(unbl[i]);
		if (i > 3 && ost > 0) {
			outm << unbl[i];
			ost--;
		}
	}
	inn.close();
	outm.close();
}
