#include <iostream>
#include <fstream>
using namespace std;

void systemOut(double** A, double* y, int n, int m)
{
    for (int i = 0; i < n; i++) //тут все ясно
    {
        for (int j = 0; j < m; j++)
        {
            cout << A[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
}

double* gaussAlg(double** A, double* y, int n, int& flag) {
    double* x, max;
    int k, index;
    const double eps = 0.0000001;
    x = new double[n];
    k = 0;
    while (k < n) {
        max = abs(A[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(A[i][k]) > max) {
                max = A[i][k];
                index = i;
            }
        }

        if (max < eps) { 
            cout << "No solutions" << endl;
            flag = 0;
            return 0;
        }

        for (int j = 0; j < n; j++) { 
            swap(A[k][j], A[index][j]);
        }

        swap(y[k], y[index]);

        for (int i = k; i < n; i++) {
            double temp = A[i][k];
            if (abs(temp) < eps) continue; 
            for (int j = 0; j < n; j++) {
                A[i][j] = A[i][j] / temp;
            }
            y[i] = y[i] / temp;  
            if (i == k) continue; 
            for (int j = 0; j < n; j++) {
                A[i][j] = A[i][j] - A[k][j]; 
            }
            y[i] = y[i] - y[k]; 
        }
        k++;
    }
  
    for (int k = n - 1; k >= 0; k--) {
        x[k] = y[k]; 
        for (int i = 0; i < k; i++) { 
            y[i] = y[i] - A[i][k] * x[k]; 
        }
    }
    return x; 
}

int main()
{
    double* x;
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
        double* y = new double[n];

        for (int i = 0; i < n; i++) A[i] = new double[m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                in >> A[i][j];
            }
            in >> y[i];
        }

        cout << endl << "Matrix introduces:" << endl;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << A[i][j] << "\t";
            cout << "\n";
        }

        cout << endl << "Formed the following system:" << endl;

        systemOut(A, y, n, m);

        cout << endl;

        x = gaussAlg(A, y, n, flag);

        if (flag) {
            cout << "Formed vector:" << endl;
            for (int i = 0; i < n; i++) {
                cout << "x[" << i << "]=" << x[i] << endl;
            }
        }
        
        for (int i = 0; i < n; i++) delete[] A[i];
        delete[] A;
        delete[] x;
        delete[] y;

        in.close();
    }
    else
    {
        cout << "File not found";
    }
}
