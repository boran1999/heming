#pragma once
#include<iostream>
#include<fstream>
#include "Heming.h"
#include "functions.h"

using namespace std;

class HemingDecode:public Heming {
public:
	HemingDecode(const char* filename, const char* filename2) :Heming(filename, filename2) {}
	void file_decoding();
	~HemingDecode();
private:
	int* decode(char a, int* &res);
};

void HemingDecode::file_decoding() {
	char res[8] = { 0 };
	int i = 0;
	for (int l = 0; l < N; l++) {
		in >> a;
		if (i == 1) {
			decode(a, splitmas);
			for (int j = 0; j < 8; j++) {
				if (j < 4)
					res[j] = mas[j];
				else
					res[j] = splitmas[j - 4];
			}
			char sym = 0;
			for (int k = 0; k < 8; k++) {
				setBit(sym, k, res[k]);
			}
			out << sym;
			i = 0;
			continue;
		}
		decode(a, mas);
		i++;
	}
	in.close();
	in.open("outnew.txt");
	N = get_amount_simbols("outnew.txt");
	unblocks("outer.txt");
	in.close();
}

int* HemingDecode::decode(char a, int* &res) {
	int check[3] = { 0 };
	for (int i = 0; i < 8; i++) {
		int viv = a & 1 << i;
		if (viv != 0)
			res[i] = 1;
		else
			res[i] = viv;
	}
	check[0] = res[0] ^ res[2] ^ res[4] ^ res[6];
	check[1] = res[1] ^ res[2] ^ res[5] ^ res[6];
	check[2] = res[3] ^ res[4] ^ res[5] ^ res[6];
	int sum = 0;
	int step = 1;
	for (int i = 0; i < 3; i++) {
		sum += check[i] * step;
		step *= 2;
	}
	if (sum != 0) {
		res[sum - 1] = !res[sum - 1];
	}
	res[0] = res[2];
	res[1] = res[4];
	res[2] = res[5];
	res[3] = res[6];
	res[4] = 0;
	res[5] = 0;
	res[6] = 0;
	res[7] = 0;
	return res;
}

HemingDecode::~HemingDecode()
{
	in.close();
	out.close();
	delete[] mas;
	delete[] splitmas;
}
