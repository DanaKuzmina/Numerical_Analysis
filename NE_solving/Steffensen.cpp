#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

double f(double x) {
    return pow(x,2) - 5 * x + 4; 
    //1E-15 -7 5 10
    //return pow(x, 2) - 2 * x + 1;
    //1E-5 -1 3 10
    //return sin(x); 
    //1E-12 -1 10 15
}

double f_second_deriv(double x) {
    return 2;
    //return -sin(x);
}

double Steff(double a, double b, double delta, int n) {
    double x0;
    int flag = 1;
    int exist = 1;
    double x, znam, xk, Xnext, f1, f2;

    while (exist) {
        for (int i = 0; flag == 1 && i < n; i++) {
            x0 = b - i * (b - a) / n;
            f1 = f_second_deriv(x0);
            f2 = f(x0);
            if (f1 * f2 > 0) {
                xk = x0;
                Xnext = x0;
                flag = 0;
            }
        }
    
        if (!flag) {
            while (xk >= a) {
                znam = f(xk + f(xk)) - f(xk);
                if (abs(znam) > delta == 0) {
                    return xk;
                }
                if (abs(znam) > delta) {
                    x = xk - f(xk) * f(xk) / znam;

                    if (abs(f(x)) < abs(f(xk))) {
                        Xnext = x;
                    }

                    if (abs(f(Xnext)) < delta) {
                        return Xnext;

                    }
                    xk = Xnext;  
                }
            }  
        }
        else {
            exist = 0;
        } 
    }
}

void main()
{
    int n;
    double a, b, delta;
    ifstream fin("input.txt");
    fstream fout("output.txt");
    if (fin.is_open()) {
        fin >> delta;
        fin >> a;
        fin >> b;
        fin >> n;
        fin.close();
        fout.seekg(0, ios::end);
        if (a > b) swap(a, b);
        double x;
        double* interval = new double[n];

        for (int i = 0; i < n; i++) {
            interval[i] = b - i * (b - a) / n;
        }

        for (int i = 0; i < n - 1; i++) {
            if (f(interval[i]) * f(interval[i + 1]) <= 0) {

                x = Steff(interval[i + 1], interval[i], delta, n);
                fout << "x = " << setprecision(10) << x << endl;
                cout << "Root: " << setprecision(10) << x << endl;
            }
        }
        fout.close();
    }

    else { 
        cout << "File not found" << endl; 
    }

}

