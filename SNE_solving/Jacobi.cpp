#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;
double f1(double x, double y) {
    //return pow(x, 2) - 5 * x + 4;
    //1E-15 -7 5 10
    return x + y - 8;
    //return pow(x, 2) - 2 * x + 1;
    //1E-5 -1 3 10
    //return sin(x); 
    //1E-12 -1 10 15
}
double f2(double x, double y) {
    return x * x + y * y - 82;
}

double df1_dx(double x) {
    return 1;
    //return -sin(x);
}

double df1_dy(double y) {
    return 1;
    //return -sin(x);
}

double df2_dx(double x) {
    return 2 * x;
    //return -sin(x);
}

double df2_dy(double y) {
    return 2 * y;
    //return -sin(x);
}

double Newton(double x, double y, double delta, int id) {
    double xk, yk;

    if (id == 1) {
        xk = x - f1(x, y) / df1_dx(x);
        return xk;
    }
    if (id == 2) {
        yk = y - f2(x, y) / df2_dy(y);
        return  yk;
    }
}


void main()
{
    setlocale(LC_ALL, "rus");
    int id, iter = 0;
    double delta;
    ifstream fin("input.txt");
    fstream fout("output.txt");
    if (fin.is_open() && fout.is_open()) {
        fin >> delta;
        fin.close();
        fout.seekg(0, ios::end);
        double x, y, xk, yk, x0, y0;
        double delta1, delta2, deltaMax;

        x0 = 9,5; y0 = -1,5;
        //x0 = -1,5; y0 = 9,5;
        //xk = 10; yk = 1;

        do{
            iter++;
            xk = Newton(x0, y0, delta, 1);
            yk = Newton(x0, y0, delta, 2);


            delta1 = abs(xk - x0);
            delta2 = abs(yk - y0);

            if (delta1 >= delta2) deltaMax = delta1;
            else deltaMax = delta2;
            x0 = xk;
            y0 = yk;

        } while (deltaMax > delta && iter <= 100000);

        if (iter > 100000) {
            cout << "Doesn't coverage" << endl;
        }

        fout << "x = " << setprecision(10) << xk << endl;
        cout << "Root x: " << setprecision(10) << xk << endl;
        fout << "y = " << setprecision(10) << yk << endl;
        cout << "Root y: " << setprecision(10) << yk << endl;
        fout.close();
    }

    else {
        cout << "File not found" << endl;
    }
}

