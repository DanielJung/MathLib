#include "stdafx.h"
#include "util.h"

using namespace ml;

double ml::util::sgn(double dValue) {
	return (dValue < 0.0) ? -1.0 : 1.0;
}

double ml::util::norm(const Matrix& oMatrix) {
	if (oMatrix.getN() != 1) {
		throw std::invalid_argument("Norm: Vector has to be Column-Vector");
	}
	double dSum = 0.0;
	for (unsigned int i = 0; i < oMatrix.getM(); ++i) {
		dSum += oMatrix(i, 0)*oMatrix(i, 0);
	}
	return sqrt(dSum);
}

Matrix ml::util::transponse(const Matrix& oMatrix) {
	Matrix oResult(oMatrix.getN(), oMatrix.getM());
	for (unsigned long i = 0; i<oMatrix.getN(); i++){
		for (unsigned long j = 0; j<oMatrix.getM(); j++){
			oResult(i, j) = oMatrix(j, i);
		}
	}
	return oResult;
}

Matrix ml::util::eye(unsigned int n) {
	Matrix M(n, n, 0.0);
	for (unsigned int i = 0; i < n; ++i) {
		M(i, i) = 1.0;
	}
	return M;
}

Matrix ml::util::eye(unsigned int n, const Matrix& oMatrix) {
	Matrix oResult = eye(n);
	for (unsigned int i = 0; i < oMatrix.getM(); ++i) {
		for (unsigned int j = 0; j < oMatrix.getM(); ++j) {
			oResult(i + (n - oMatrix.getM()), j + (n - oMatrix.getN())) = oMatrix(i, j);
		}
	}
	return oResult;
}

Matrix ml::util::UnitVector(unsigned int iN, unsigned int iI) {
	Matrix oResult(iN, 0.0);
	oResult(iI, 0) = 1.0;
	return oResult;
}

void ml::util::lu(const Matrix& oMatrixA, Matrix& oMatrixL, Matrix& oMatrixR) {
	if (oMatrixA.getM() != oMatrixA.getN()){
		throw "Matrix dimensions must agree";
	}
	unsigned long n = oMatrixA.getM();
	oMatrixR = oMatrixA;

	oMatrixL = eye(n);

	for (unsigned long k = 0; k<n; k++){
		for (unsigned long i = k + 1; i<n; i++){
			oMatrixL(i, k) = oMatrixR(i, k) / oMatrixR(k, k);
			for (unsigned long j = k + 1; j<n; j++){
				oMatrixR(i, j) =  oMatrixR(i, j) - oMatrixL(i, k)*oMatrixR(k, j);
			}
			oMatrixR(i, k) = 0.0;
		}
	}
}

void ml::util::qr(const Matrix& oMatrixA, Matrix& oMatrixQ, Matrix& oMatrixR) {
	std::vector<Matrix> aQ;
	Matrix A(oMatrixA);
	for (unsigned int i = 0; i < oMatrixA.getN() - 1; ++i) {
		double alpha = util::sgn(A(0, 0))*util::norm(A.getCol(0));
		Matrix v = A.getCol(0) + alpha*util::UnitVector(A.getM(), 0);
		Matrix Q = util::eye(v.getM()) - (2.0*v*util::transponse(v)) / (util::transponse(v)*v);
		aQ.push_back(Q);
		A = (Q*A).subMatrix(1, 1);
		cout << "A_Neu: " << A << endl;
	}
	oMatrixR = oMatrixA;
	for (unsigned int i = 0; i < aQ.size(); ++i) {
		oMatrixR = aQ[i] * oMatrixR;
	}
	oMatrixQ = util::transponse(aQ[aQ.size() - 1]);
	for (unsigned int i = aQ.size() - 2; i >= 0; ++i) {

	}
}

Matrix ml::util::solve(const Matrix& oMatrix, const Matrix& oVector) {
	return Matrix(0.0);
}