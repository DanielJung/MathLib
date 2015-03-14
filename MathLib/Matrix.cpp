#include "stdafx.h"
#include "Matrix.h"

#include <iomanip>

using namespace ml;

#define dEps 10e-10

Matrix::Matrix(double dData) : mdData(new double(dData)), miM(1), miN(1) {

}

Matrix::Matrix(unsigned int iM) : mdData(new double[iM]), miM(iM), miN(1) {

}

Matrix::Matrix(unsigned int iM, unsigned int iN) : mdData(new double[iM*iN]), miM(iM), miN(iN) {

}

Matrix::Matrix(unsigned int iM, double dData) : mdData(new double[iM]), miM(iM), miN(1) {
	for (unsigned int i = 0; i < miM; ++i) {
		mdData[i] = dData;
	}
}

Matrix::Matrix(unsigned int iM, const double* dData) : mdData(NULL), miM(iM), miN(1) {
	mdData = new double[miM];
	for (unsigned int i = 0; i < miM; ++i) {
		mdData[i] = dData[i];
	}
}

Matrix::Matrix(unsigned int iM, unsigned int iN, double dData) : mdData(new double[iM*iN]), miM(iM), miN(iN) {
	for (unsigned int i = 0; i < iM*iN; ++i) {
		mdData[i] = dData;
	}
}

Matrix::Matrix(unsigned int iM, unsigned int iN, const double* dData) : mdData(new double[iM*iN]), miM(iM), miN(iN) {
	for (unsigned int i = 0; i < miM*miN; ++i) {
		mdData[i] = dData[i];
	}
}

Matrix::Matrix(const Matrix& oMatrix) : mdData(new double[oMatrix.getM()*oMatrix.getN()]), miM(oMatrix.getM()), miN(oMatrix.getN()) {
	memcpy(mdData, oMatrix.getData(), miM*miN*sizeof(double));
}

Matrix::~Matrix() {
	delete[] mdData;
	miM = 0;
	miN = 0;
}

unsigned int Matrix::getM() const {
	return miM;
}

unsigned int Matrix::getN() const {
	return miN;
}

double& Matrix::operator() (unsigned int iI, unsigned int iJ) {
	return mdData[iI*getN() + iJ];
}

double Matrix::operator() (unsigned int iI, unsigned int iJ) const {
	return mdData[iI*getN() + iJ];
}

Matrix Matrix::getRow(unsigned int iI) const {
	return Matrix(1, getN(), &mdData[iI*getN()]);
}

Matrix Matrix::getCol(unsigned int iJ) const {
	Matrix oResult(getM());
	for (unsigned int i = 0; i < getM(); ++i) {
		oResult(i, 0) = (*this)(i, iJ);
	}
	return oResult;
}

Matrix Matrix::subMatrix(unsigned int iIShift, unsigned int iJShift, unsigned int iM, unsigned int iN) {
	if (iM == 0) iM = getM() - iIShift;
	if (iN == 0) iN = getN() - iJShift;
	Matrix oResult(iM, iN);
	for (unsigned int i = 0; i < iM; ++i) {
		for (unsigned int j = 0; j < iN; ++j) {
			oResult(i, j) = (*this)(i + iIShift, j + iJShift);
		}
	}
	return oResult;
}

Matrix& Matrix::operator =(const Matrix& oMatrix) {
	miM = oMatrix.getM();
	miN = oMatrix.getN();
	delete[] mdData;
	mdData = new double[oMatrix.getN()*oMatrix.getM()];
	memcpy(mdData, oMatrix.getData(), miM*miN*sizeof(double));
	return *this;
}

Matrix& Matrix::operator =(double dValue) {
	miM = 1;
	miN = 1;
	delete[] mdData;
	mdData = new double[1];
	mdData[0] = dValue;
	return *this;
}

Matrix& Matrix::operator +=(const Matrix& oMatrix) {
	for (unsigned int i = 0; i < getM()*getN(); ++i) {
		mdData[i] += oMatrix.getData()[i];
	}
	return *this;
}

Matrix& Matrix::operator +=(const double dValue) {
	for (unsigned int i = 0; i < getM()*getN(); ++i) {
		mdData[i] += dValue;
	}
	return *this;
}

Matrix& Matrix::operator -=(const Matrix& oMatrix) {
	for (unsigned int i = 0; i < getM()*getN(); ++i) {
		mdData[i] -= oMatrix.getData()[i];
	}
	return *this;
}

Matrix& Matrix::operator -=(const double dValue) {
	for (unsigned int i = 0; i < getM()*getN(); ++i) {
		mdData[i] -= dValue;
	}
	return *this;
}

Matrix& Matrix::operator *=(const Matrix& oMatrix) {
	double* mdDataCpy = new double[getM()*oMatrix.getN()];

	for (unsigned int i = 0; i < getM(); ++i) {
		for (unsigned int j = 0; j < oMatrix.getN(); ++j) {
			double sum = 0.0;
			for (unsigned int k = 0; k < getN(); ++k) {
				sum += mdData[i*getN()+k] * oMatrix.getData()[k*oMatrix.getN()+j];
			}
			mdDataCpy[i*oMatrix.getN()+j] = sum;
		}
	}
	
	delete[] mdData;
	mdData = mdDataCpy;
	miM = getM();
	miN = oMatrix.getN();
	return *this;
}

Matrix& Matrix::operator *=(const double dValue) {
	for (unsigned int i = 0; i < getM()*getN(); ++i) {
		mdData[i] *= dValue;
	}
	return *this;
}

Matrix& Matrix::operator /= (const Matrix& oMatrix) {
	if (oMatrix.getM() != 1 || oMatrix.getN() != 1)	throw std::invalid_argument("Error /=: matrix dimensions must agree");
	return (*this) /= oMatrix(0, 0);
}

Matrix& Matrix::operator /= (const double dValue) {
	return (*this)*=(1 / dValue);
}

const double* Matrix::getData() const {
	return mdData;
}

Matrix ml::operator + (const Matrix& oMatrix1, const Matrix& oMatrix2) {
	return Matrix(oMatrix1) += oMatrix2;
}

Matrix ml::operator + (const Matrix& oMatrix, const double dValue) {
	return Matrix(oMatrix) += dValue;
}

Matrix ml::operator + (const double dValue, const Matrix& oMatrix) {
	return oMatrix + dValue;
}

Matrix ml::operator - (const Matrix& oMatrix1, const Matrix& oMatrix2) {
	return Matrix(oMatrix1) -= oMatrix2;
}

Matrix ml::operator - (const Matrix& oMatrix, const double dValue) {
	return Matrix(oMatrix) -= dValue;
}

Matrix ml::operator - (const double dValue, const Matrix& oMatrix) {
	if (oMatrix.getM() == 1 && oMatrix.getN() == 1) {
		return dValue - oMatrix;
	}
	throw std::invalid_argument("operator - : Matrix dimensions must agree");
}

Matrix ml::operator * (const Matrix& oMatrix1, const Matrix& oMatrix2) {
	return Matrix(oMatrix1) *= oMatrix2;
}

Matrix ml::operator * (const Matrix& oMatrix, const double dValue) {
	return Matrix(oMatrix) *= dValue;
}

Matrix ml::operator * (const double dValue, const Matrix& oMatrix) {
	return oMatrix*dValue;
}

Matrix ml::operator / (const Matrix& oMatrix1, const Matrix& oMatrix2) {
	return Matrix(oMatrix1) /= oMatrix2;
}

Matrix ml::operator / (const Matrix& oMatrix, const double dValue) {
	return oMatrix*(1.0 / dValue);
}

Matrix ml::operator / (const double dValue, const Matrix& oMatrix) {
	if (oMatrix.getM() == 1 && oMatrix.getN() == 1) {
		return dValue / oMatrix(0, 0);
	}
	throw std::invalid_argument("operator /: matrix dimensions must agree");
}

bool ml::operator == (const Matrix& oMatrix1, const Matrix& oMatrix2) {
	if (oMatrix1.getM() != oMatrix2.getM() || oMatrix1.getN() != oMatrix2.getN())	return false;
	for (unsigned int i = 0; i < oMatrix1.getM()*oMatrix1.getN(); ++i) {
		if (abs(oMatrix1.getData()[i] - oMatrix2.getData()[i])>dEps)	return false;
	}
	return true;
}

bool ml::operator == (const Matrix& oMatrix, const double dValue) {
	return (oMatrix.getN() == 1 && oMatrix.getM() == 1 && abs(oMatrix(0, 0) - dValue) < dEps);
}

bool ml::operator == (const double dValue, const Matrix& oMatrix) {
	return oMatrix == dValue;
}

std::ostream& ml::operator <<(std::ostream& oStream, const Matrix& oMatrix) {
	oStream.fill(' ');
	oStream.precision(9);
	oStream << endl;
	for (unsigned long i = 0; i<oMatrix.getM(); ++i)
	{
		oStream << setw(10) << ((abs(oMatrix(i, 0))<dEps) ? 0 : oMatrix(i, 0));
		for (unsigned long j = 1; j<oMatrix.getN(); ++j)
		{
			oStream << " " << setw(10) << ((abs(oMatrix(i, j))<dEps) ? 0 : oMatrix(i, j));
		}
		oStream << endl;
	}
	oStream << std::resetiosflags(std::ios::showbase);
	return oStream;
}