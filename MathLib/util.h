#pragma once

#include "Matrix.h"

namespace ml {
	namespace util {
		double sgn(double dValue);

		double norm(const Matrix& oMatrix);

		Matrix transponse(const Matrix& oMatrix);

		Matrix eye(unsigned int n);
		Matrix eye(unsigned int n, const Matrix& oMatrix);
		Matrix UnitVector(unsigned int iN, unsigned int iI);

		void lu(const Matrix& oMatrixA, Matrix& oMatrixL, Matrix& oMatrixR);
		void qr(const Matrix& oMatrixA, Matrix& oMatrixQ, Matrix& oMatrixR);

		Matrix solve(const Matrix& oMatrix, const Matrix& oVector);
	}
}