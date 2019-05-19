#pragma once
#include<iostream>
#include<fstream>
#include "Heming.h"
#include "functions.h"

using namespace std;

class HemingCode:public Heming
{
public:
	HemingCode(const char* filename, const char* filename2) :Heming(filename, filename2) {}
	void file_encoding();
	~HemingCode();
private:
	char code(int*a);
};

void HemingCode::file_encoding() {
	blocks("temp.txt");
	in.close();
	in.open("temp.txt");
	N = get_amount_simbols("temp.txt");
	for (int l = 0; l < N; l++) {
		in >> a;
		for (int i = 0; i < 8; i++) {
			splitmas[i] = 0;
			int viv = a & (1 << i);
			if (viv != 0)
				mas[i] = 1;
			else
				mas[i] = viv;
		}
		for (int i = 0; i < 8; i++) {
			if (i < 4)
				splitmas[i] = mas[i];
			else {
				mas[i - 4] = mas[i];
				mas[i] = 0;
			}
		}
		out << code(splitmas) << code(mas);
	}
	in.close();
}

char HemingCode::code(int*a) {
	int res[8] = { 0 };
	res[2] = a[0];
	res[4] = a[1];
	res[5] = a[2];
	res[6] = a[3];
	res[0] = res[2] ^ res[4] ^ res[6];
	res[1] = res[2] ^ res[5] ^ res[6];
	res[3] = res[4] ^ res[5] ^ res[6];
	char sim;
	for (int i = 0; i < 7; i++) {
		res[7] ^= res[i];
		setBit(sim, i, res[i]);
	}
	setBit(sim, 7, res[7]);
	return sim;
}

HemingCode::~HemingCode()
{
	in.close();
	out.close();
	delete[] mas;
	delete[] splitmas;
}
