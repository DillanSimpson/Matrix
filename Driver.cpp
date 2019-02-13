#include <iostream>
#include <vector>
#include "Matrix.h"
using namespace std;
int main()
{
	matrix<int> m1(3,3);
	matrix<int> m2(2, 3);
	matrix<int> m3{{ 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 }};
	matrix<int> m4(3, 5);
	matrix<int> m5(3, 3);
	matrix<int> m6{ { 3, 0, -1, 2 },{ 4, 1, 3, -2 },{ 0, 2, -1, 3 },{ 1, 0, 1, 4 } };
	matrix<int> m7(4, 4);
	vector<int> v1{ 1, 2, 3 };
	vector<int> v2{ 2, 3, 4 };
	matrix<int> t1{ {1,2,4}, {2,4,1}, {3,4,5} };
	matrix<int> t2{ { 3,8,4 },{ 1,4,1 }, {2,3,4} };
	matrix<int> t3(3, 3);

	//Testing side effects
	t3 = t1 + t2;
	cout << t1 << endl;
	cout << t2 << endl;
	cout << "No side effect " << endl;

	t3 = t1 * 3;
	cout << t1 << endl;
	cout << "No side effect " << endl;

	cout << "m3 =\n";
	cout << m3 << endl;
	cout << "Enter 3 x 3 matrix row by row:\n";
	cin >> m1;
	cout << "Enter 3 x 2 matrix row by row:\n";
	cin >> m2;
	cout << "m1:\n";
	cout << m1;
	cout << "m2:\n";
	cout << m2;
	cout << "m1 + m3\n";
	cout << m1 + m3 << endl;
	cout << "m1 = " << endl << m1 << endl;
	cout << "m2 = " << endl << m2 << endl;
	cout << "m5 += m1 += m1\n";
	cout << (m5 += (m1 += m1)) << endl;
	cout << "m1 = " << endl << m1 << endl;
	cout << "m5 = " << endl << m5 << endl;
	cout << "m1 * m2\n";
	cout << m1 * m2 << endl;
	cout << "m1 = " << endl << m1 << endl;
	cout << "m2 = " << endl << m2 << endl;
	cout << "m1*3\n";
	cout << m1 * 3 << endl;
	cout << "m1.transpose\n";
	cout << m1.t() << endl;
	cout << "m1 = " << endl << m1 << endl;
	cout << "v1 = " << v1[0] << " " << v1[1] << " " << v1[2] << endl;
	cout << "v2 = " << v2[0] << " " << v2[1] << " " << v2[2] << endl;
	cout << "v1 dot v2 = " << dot(v1, v2) << endl;
	cout << "m1:\n";
	cout << m1;
	cout << "Testing the creation of new array from m1 by removing row " << m1.numrows() - 1
		<< " of m1 " << endl;
	cout << m1.deleteRow(m1.numrows() - 1) << endl;
	cout << "Testing the creation of new array from m1 by removing col " << m1.numcols() - 1
		<< " of m1 " << endl;
	cout << m1.deleteCol(m1.numcols() - 1) << endl;
	cout << "m6:\n";
	cout << m6 << endl;
	cout << "Determinant of m6 = " << m6.det() << endl;
	cout << "m7 = I(4):" << endl << (m7 = eye<int>(4)) << endl;
	cout << "zeroes(4,4):" << endl << zeroes<int>(4, 4) << endl;
	cout << "ones(4,4):" << endl << ones<int>(4, 4) << endl;
	
	
	return 0;
}