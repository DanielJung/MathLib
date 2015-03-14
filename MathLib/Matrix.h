#pragma once

#include <iostream>

namespace ml {
	class Matrix
	{
	public:
		Matrix(double dData);
		Matrix(unsigned int iM);
		Matrix(unsigned int iM, unsigned int iN);
		Matrix(unsigned int iM, double dData);
		Matrix(unsigned int iM, const double* dData);
		Matrix(unsigned int iM, unsigned int iN, double dData);
		Matrix(unsigned int iM, unsigned int iN, const double* dData);
		Matrix(const Matrix& oMatrix);
		virtual ~Matrix();

		unsigned int getM() const;
		unsigned int getN() const;

		double& operator() (unsigned int iI, unsigned int iJ);
		double operator() (unsigned int iI, unsigned int iJ) const;

		Matrix getRow(unsigned int iI) const;
		Matrix getCol(unsigned int iJ) const;

		Matrix subMatrix(unsigned int iIShift, unsigned int iJShift, unsigned int iM = 0, unsigned int iN = 0);

		Matrix& operator =(const Matrix& oMatrix);
		Matrix& operator =(const double dValue);
		Matrix& operator +=(const Matrix& oMatrix);
		Matrix& operator +=(const double dValue);
		Matrix& operator -=(const Matrix& oMatrix);
		Matrix& operator -=(const double dValue);
		Matrix& operator *=(const Matrix& oMatrix);
		Matrix& operator *=(const double dValue);
		Matrix& operator /=(const Matrix& oMatrix);
		Matrix& operator /=(const double dValue);

		const double* getData() const;
	protected:
		double* mdData;

		unsigned int miM;
		unsigned int miN;
	};

	bool operator == (const Matrix& oMatrix1, const Matrix& oMatrix2);
	bool operator == (const Matrix& oMatrix, const double dValue);
	bool operator == (const double dValue, const Matrix& oMatrix);
	Matrix operator + (const Matrix& oMatrix1, const Matrix& oMatrix2);
	Matrix operator + (const Matrix& oMatrix, double dValue);
	Matrix operator + (const double dValue, const Matrix& oMatrix);
	Matrix operator - (const Matrix& oMatrix1, const Matrix& oMatrix2);
	Matrix operator - (const Matrix& oMatrix, const double dValue);
	Matrix operator - (const double dValue, const Matrix& oMatrix);
	Matrix operator * (const Matrix& oMatrix1, const Matrix& oMatrix2);
	Matrix operator * (const Matrix& oMatrix, const double dValue);
	Matrix operator * (const double dValue, const Matrix& oMatrix);
	Matrix operator / (const Matrix& oMatrix1, const Matrix& oMatrix2);
	Matrix operator / (const Matrix& oMatrix, const double dValue);
	Matrix operator / (const double dValue, const Matrix& oMatrix);

	std::ostream& operator <<(std::ostream& oStream, const Matrix& oMatrix);
}