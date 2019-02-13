#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdlib.h>

using namespace std;

template<typename T>
matrix<T> matrix<T>::t() const
{
	matrix<T> transpose(numcols(), numrows());
	for (int i = 0; i < numrows(); i++) {
		for (int j = 0; j < numcols(); j++) {
			transpose[j][i] = arr[i][j];
		}
	}
	return transpose;
}

template <typename T>
const matrix<T> & matrix<T>::operator=(const matrix<T> & rhs)
{
	assert(this->numrows() == rhs.numrows() && this->numcols() == rhs.numcols());
	for (int i = 0; i < rhs.numrows(); i++) {
		for (int j = 0; j < rhs.numcols(); j++) {
			arr[i][j] = rhs[i][j];
		}
	}
	return *this;
}

template<typename T>
const matrix<T> matrix<T>::operator+=(const matrix<T> & rhs) {
	assert(this->numrows() == rhs.numrows() && this->numcols() == rhs.numcols());
	for (int i = 0; i < rhs.numrows(); i++) {
		for (int j = 0; j < rhs.numcols(); j++) {
			arr[i][j] += rhs[i][j];
		}
	}
	return *this;
}

template<typename T>
const matrix<T> matrix<T>::operator+ (const matrix<T> & rhs) const {
	assert(this->numrows() == rhs.numrows() && this->numcols() == rhs.numcols());
	matrix<T> temp(this->numrows(),this->numrows());
	temp = *this;
	return temp += rhs;
}

template<typename T>
const matrix<T> matrix<T>::operator*= (const T &c) {
	for (int i = 0; i < this->numrows(); i++) {
		for (int j = 0; j < this->numcols(); j++) {
			arr[i][j] *= c;
		}
	}
	return *this;
}

template<typename T>
const matrix<T> matrix<T>::operator* (const T &c) const {
	matrix<T> temp(this->numrows(), this->numrows());
	temp = *this;
	return temp *= c;
}

template<typename T>
const matrix<T> matrix<T>::operator* (const matrix<T> & rhs)const {
	assert(this->numrows() == rhs.numcols());
	matrix<T> mult(rhs.numrows(), this->numcols());
	for (int i = 0; i < rhs.numrows(); i++) {
		for (int j = 0; j < this->numcols(); j++) {
			mult[i][j] = 0;
			for (int k = 0; k < this->numcols(); k++) {
				mult[i][j] += (arr[i][k] * rhs[i][j]);
			}
		}
	}
	return mult;
}

template<typename T>
vector<T> matrix<T>::row(int k) const {
		for (int i = 0; i < (*this).numrows(); i++) {
			if (i == k) {
				return arr.at(i);
			}
	}
}

template<typename T>
vector<T> matrix<T>::col(int k) const {
	vector<T> col;
	for (int i = 0; i < (*this).numrows(); i++) {
		for (int j = 0; j < (*this).numcols(); j++) {
			if (k == j) {
				col.push_back(arr[i][j]);
			}
		}
	}
	return col;
}

template<typename T>
matrix<T> matrix<T>::deleteRow(int k) const {
		matrix<T> temp(numrows()-1, numcols());
		for (int i = 0; i < numrows(); i++) {
			for (int j = 0; j < numcols(); j++) {
				if (i != k) {
					temp[i][j] = arr[i][j];
				}
			}
		}
		return temp;
}

template<typename T>
matrix<T> matrix<T>::deleteCol(int k) const {
	matrix<T> temp(numrows(), numcols()-1);
	for (int i = 0; i < numrows(); i++) {
		for (int j = 0; j < numcols(); j++) {
			if (j != k) {
				temp[i][j] = arr[i][j];
			}
		}
	}
	return temp;
}

template <typename T>
T matrix<T>::det_aux() {
	T sum;
	if (this->numrows() == 0)
		return 0;
	else if (this->numrows() == 1)
		return this->arr[0][0];
	else if (this->numrows() == 2)
		return this->arr[0][0] * this->arr[1][1]
		- this->arr[1][0] * this->arr[0][1];
	else {
		sum = T();
		for (int k = 0; k < this->numcols(); k++) {
			sum += arr[0][k] * pow(-1, 0 + k)* det_aux();
		}
	}
	return sum;
}

template <typename T>
T matrix<T>::det()
{
	assert(this->numrows() == this->numcols());
	return this->det_aux();
}

template<typename T>
void matrix<T>::read(istream & in) {
	int totalElements = numrows()*numcols();
	for (int i = 0; i < numrows(); i++)
		for (int j = 0; j < numcols(); j++)
			this->arr[i][j] = T();
	if (this->numrows() == 0) return;
	int numberOfElements = 0;
	while (numberOfElements < totalElements && in >> ws && !in.eof()) {
		T element;
		numberOfElements++;
		in >> element;
		this->arr[(numberOfElements - 1) / numcols()][(numberOfElements - 1) % numcols()]
			= element;
	}
}

template<typename T>
void matrix<T>::print(ostream & out) const {
	for (int i = 0; i < numrows(); i++) {
		cout << this->arr[i][0];
		for (int j = 1; j < numcols(); j++)
			cout << " " << this->arr[i][j];
		cout << endl;
	}
}

template<typename T>
istream& operator>>(istream & in, matrix<T> & rhs) {
	rhs.read(in);
	return in;
}

template<typename T>
ostream& operator<<(ostream & out, const matrix<T> & rhs) {
	rhs.print(out);
	return out;
}

template<typename T>
T dot(const vector<T> & lvec, const vector<T> & rvec) {
	T dotProd = 0;
	for (size_t i = 0; i < lvec.size(); i++) {
			dotProd += lvec[i] + rvec[i];
	}
	return dotProd;
}

template<typename T>
matrix<T> eye(int n) {
	matrix<T> eyeMat(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++){
			if (i == j) {
				eyeMat[i][j] = 1;
			}
			else {
				eyeMat[i][j] = 0;
			}
		}
	}
	return eyeMat;
}

template<typename T>
matrix<T> zeroes(int rows, int cols) {
	matrix<T> zeroes(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			zeroes[i][j] = 0;
		}
	}
	return zeroes;
}

template<typename T>
matrix<T> ones(int rows, int cols) {
	matrix<T> ones(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			ones[i][j] = 1;
		}
	}
	return ones;
}
#endif