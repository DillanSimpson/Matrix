//matrix.h file
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
using namespace std;
template <typename T>
class matrix
{
public:
	// construct a (0x0) empty matrix-of-int T.
	matrix() :arr(0)
	{}
	// constructs rows x cols matrix-of-int T.
	matrix(int rows, int cols)
	{
		for (int i = 0; i < rows; i++) {
			vector<T> temp;
			for (int j = 0; j < cols; j++) {
				temp.push_back(0);
			}
			arr.push_back(temp);
		}
	}

//constructs an (nxm) matrix, determined by the number of elements in the initializer list { {...}...{...}
matrix(initializer_list<vector<T>> lst) : arr(lst.size())
{
	const vector<T> *it = lst.begin(); 
	int j = 0;
	while (it != lst.end()) {
		const T* num = it->data();
		vector<T> temp;
		for (size_t i = 0; i < it->size(); i++) {
			temp.push_back(*(num + i));
		}
			arr.at(j) = temp;
			j++;
		it++;
	}
}

//Copy constructor(L - Ref parameter)
matrix(const vector<vector<T>> & v) : arr{ v }
{ }
//Move constructor(R - Ref parameter)
matrix(vector<vector<T>> && v) : arr{ std::move(v) }
{ }
// returns the k-th row; constversion
const vector<T> & operator[](int row) const
{
	return arr[row];
}
// returns the k-th row; npn-const version
vector<T> & operator[](int row)
{
	return arr[row];
}
int numrows() const
{
	int rows = 0;
	for (size_t i = 0; i < arr.size(); i++) {
		for (size_t j = 0; j < arr[i].size(); j++) {
			rows = i + 1;
		}
	}
	return rows;
}
int numcols() const
{
	int cols = 0;
	for (size_t i = 0; i < arr.size(); i++) {
		for (size_t j = 0; j < arr[i].size(); j++) {
			cols = j + 1;
		}
	}
	return cols;
}

matrix<T> t() const; //returns a new matrix that is the transpose of *this
const matrix<T> & operator=(const matrix<T> & rhs); //assignment operator
const matrix<T> operator+=(const matrix<T> & rhs); //matrix-matrix addition (mutator)
const matrix<T> operator+ (const matrix<T> & rhs) const; //matrix-matrix addition (nonmutator)
const matrix<T> operator*= (const T &c); //scalar multiplication (mutator)
const matrix<T> operator*(const T &c) const; //scalar multiplication (non-mutator)
const matrix<T> operator* (const matrix<T> & rhs)const; //matrix-matrix multiplication (non - mutator)
vector<T> row(int k) const; //returns a new vector (non-mutator), a copy ofthe kth - row of *this
vector<T> col(int k) const; //returns a new vector (non-mutator), a copy of the kth - row of *this
matrix<T> deleteRow(int k) const; //returns a new T (non-mutator), a copy of *this with kth row deleted
matrix<T> deleteCol(int k)const; //returns a new T (non-mutator), a copy of *this with kth column deleted
T det(); //returns the determinant of *this
		 //Matrix input / output member functions(both use row - major order; read mutates *this T.)
void read(istream & in = cin);
void print(ostream & out = cout) const;
private:
	vector<vector<T>> arr;
	T det_aux(); //helper function for the public determinant function, member det().
};
//non-member matrix-related function: dot product of two vectors
template<typename T>
T dot(const vector<T> & lvec, const vector<T> & rvec);
//non-member matrix-related function: returns an (n x n) identity matrix
template<typename T>
matrix<T> eye(int n);
//non-member matrix-related function: returns an (row x col) matrix filled with zeroes (0's)
template<typename T>
matrix<T> zeroes(int rows, int cols);
//non-member matrix-related function: returns an (row x col) matrix filled with ones (1's)
template<typename T>
matrix<T> ones(int rows, int cols);
// used to bind a matrix (in row-major order) to element values using the stream extraction operator and istream T
template<typename T>
istream& operator>>(istream & in, matrix<T> & rhs);
// used to output a matrix (in row-major order) using the stream insertion operator and ostream T
template<typename T>
ostream& operator<<(ostream & out, const matrix<T> & rhs);
#include "Matrix.cpp"
#endif