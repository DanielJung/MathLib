// MathLibTest.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include "Matrix.h"
#include "util.h"

#include <iostream>
#include <ctime>

using namespace std;
using namespace ml;


int _tmain(int argc, _TCHAR* argv[])
{
	double dataA[] = {1, 2, 3, 4, 5, 6};
	double dataB[] = { 1, 1, 1, 1, 1, 1 };
	double dataD[] = { 6, 5, 4, 3, 2, 1 };

	Matrix A(3, 2, dataA);

	Matrix B(3, 2, dataB);

	Matrix C = A + B;

	Matrix D(2, 3, dataD);

	Matrix E = 42.0;

	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C: " << C << endl;
	cout << "D: " << D << endl;
	cout << "A*D: " << A*D << endl;
	cout << "E: " << E << endl;

	system("pause");
	return 0;
}

