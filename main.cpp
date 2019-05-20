#include<iostream>
#include<fstream>
#include "functions.h"
#include "HemingCode.h"
#include "HemingDecode.h"

using namespace std;

int main(void) {
	setlocale(LC_ALL, "Russian");
	char vib;
	cout << "Вы хотите закодировать или декодировать файл? (e/d)" << endl;
	cin >> vib;
	if (vib == 'e') {
		HemingCode code("in.txt", "encoding_result.txt");
		code.file_encoding();
		cout << "Файл закодирован" << endl;
	}
	else if (vib == 'd') {
		HemingDecode dec("encoding_result.txt", "tempout.txt");
		dec.file_decoding();
		cout << "Файл декодирован" << endl;
	}
	else {
		cout << "Хорошего времени суток" << endl;
		exit;
	}
	system("pause");
	return 0;
}
