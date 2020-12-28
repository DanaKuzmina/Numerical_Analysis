#include <iostream>
#include <fstream>
 
using namespace std;

void LUdecompose(double** A, double** LU, int n) {
	double sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i <= j) {
				sum = 0;
				if (i != 0) {
					for (int k = 0; k < i; k++) {
						sum += LU[i][k] * LU[k][j];
					}
				}
				LU[i][j] = A[i][j] - sum;
			}

			if (i > j) {
				sum = 0;
				if (j != 0) {
					for (int k = 0; k < j; k++) {
						sum += LU[i][k] * LU[k][j];
					}
				}
				LU[i][j] = (1 / LU[j][j]) * (A[i][j] - sum);
			}
		}
	}
}

void resolveMatrix(double** LU, double* x, double* b, int n) {
	double* y = new double[n];
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum = 0;
		if (i != 0) {
			for (int p = 0; p < i; p++) {
				sum += LU[i][p] * y[p];
			}
		}
		y[i] = b[i] - sum;
	}

	for (int i = 0; i < n; i++) {
		sum = 0;
		for (int p = 0; p < i; p++) {
			sum += LU[n - i-1][n - p-1] * x[n - p - 1];
		}
		x[n-i-1] = (1/LU[n-i-1][n-i-1])*(y[n-i-1] - sum); 
	}
}


int main() {
	int flag = 1;

	ifstream in("input.txt");
	if (in.is_open())
	{
		int count = 0;
		double temp;

		while (!in.eof())
		{
			in >> temp; 
			count++; 
		}

		in.seekg(0, ios::beg);
		in.clear();
		int count_space = 0;
		char symbol;

		while (!in.eof())
		{
			in.get(symbol);
			if (symbol == ' ') count_space++; 
			if (symbol == '\n') break; 
		}

		in.seekg(0, ios::beg);
		in.clear();

		int n = count / (count_space + 1);
		int m = count_space; 
		double** A = new double* [n];
		double* b = new double[n];
		double* x = new double[n];
		double** LU = new double* [n];

		for (int i = 0; i < n; i++) {
			A[i] = new double[m];
			LU[i] = new double[m];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				in >> A[i][j];
			}
			in >> b[i];
		}

		cout << endl << "Matrix introduces:" << endl;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << A[i][j] << "\t";
			cout << "\n";
		}

		LUdecompose(A, LU, n);

		resolveMatrix(LU, x, b, n);

		cout << endl;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
				cout << LU[i][j] << "\t";
			cout << "\n";
		}

		cout << endl;

		for (int i = 0; i < n; i++)
		{
			cout << x[i];
			cout << "\n";
		}
	}
}
