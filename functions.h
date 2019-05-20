#pragma once
#include<iostream>
#include<fstream>

using namespace std;

int get_amount_simbols(const char* filename) {
	ifstream in(filename);
	int N = 0;
	char sym;
	while (!in.eof()) {
		in.get(sym);
		N++;
	}
	N -= 1;
	return N;
}

void setBit(char& b, int i, char bit)
{
	b = (bit == 1) ? b | (1 << i) : b & ~(1 << i);
}

char getBit(char b, int i)
{
	b = b & (1 << i);
	b = b != 0 ? 1 : 0;
	return b;
}
