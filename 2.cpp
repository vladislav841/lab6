#include <iostream>
#include<vector>
#include<cmath>
#include<math.h>
using namespace std;
double function(vector<double> x) {
    return pow(x[0], 2) + 8*x[0]+ 5*pow(x[1], 2) + 7*pow(x[2], 2) + 119.0*x[2] + 531.75;
}
double NormEvklid(vector<double> vectors) {
    double norm = 0;
    for (int i = 0; i < vectors.size(); i++) {
        norm += vectors[i] * vectors[i];
    }
    return sqrt(norm);
}
double DFDXi(vector<double> x, int i) {
    double dxi = pow(10, -5);
    vector < double > newX;
    for (int k = 0; k < 3; k++) {
        if (k == (i - 1)) {
            newX.push_back(x[k] + dxi);
        }
        else
        newX.push_back(x[k]);
    }
    return  (function(newX) - function(x)) / dxi;
}
double DF2DXi2(vector<double> x, int i) {
    double dxi = pow(10, -5);
    vector < double > newX1;
    for (int k = 0; k < 3; k++) {
        if (k == (i - 1)) {
            newX1.push_back(x[k] + dxi);
        }
        else
        newX1.push_back(x[k]);
    }
    vector < double >newX2;
    for (int k = 0; k < 3; k++) {
        if (k == (i - 1)) {
            newX2.push_back(x[k] - dxi);
        }
        else
        newX2.push_back(x[k]);
    }
    return (function(newX1) - 2 * function(x) + function(newX2)) / pow(dxi, 2);
}
double DF2DXiDXj(vector<double> x, int i, int j) {
    double dxi = pow(10, -5), dxj = pow(10, -5);
    vector<double> newX1;
    vector<double> newX2;
    vector<double> newX3;
    for (int k = 0; k < 3; k++) {
        if (k == (i - 1)) {
            newX1.push_back(x[k] - dxi);
        }
        else
        newX1.push_back(x[k]);
    }
    for (int k = 0; k < 3; k++) {
        if (k == (j - 1)) {
            newX2.push_back(x[k] - dxj);
        }
        else
        newX2.push_back(x[k]);
    }
    for (int k = 0; k < 3; k++) {
        if (k == (i - 1)) {
            newX3.push_back(x[k] - dxi);
        }
        else if (k == (j - 1)) {
            newX3.push_back(x[k] - dxj);
        }
        else
        newX3.push_back(x[k]);
    }
    return (function(x) - function(newX1) - function(newX2) + function(newX3)) / (dxi * dxj);
}
vector<double> gradient(vector<double>x) {
    vector < double > grad = { DFDXi(x,1),DFDXi(x,2), DFDXi(x,3) };
    return grad;
}
double functionOneVariable(vector<double> x, double tk) {
    vector < double > grad = gradient(x);
    vector<double> newVector = { x[0] - tk * grad[0], x[1] - tk * grad[1] , x[2] - tk * grad[2] };
    return function(newVector);
}
double GoldenSearch(vector<double> x, double eps) {
    double tmin = 0.01, tmax = 10;
    double y0, z0;
    while (fabs(tmin - tmax) > eps) {
        y0 = tmax - (tmax - tmin) / ((1 + sqrt(5)) / 2);
        z0 = tmin + (tmax - tmin) / ((1 + sqrt(5)) / 2);
        if (functionOneVariable(x, y0) > functionOneVariable(x, z0))
            tmin = y0;
        else
            tmax = z0;
    }
    return (tmax + tmin) / 2;
}
void step3(vector<double> x, double eps) {
    if (NormEvklid(gradient(x)) < eps) {
        cout << "Solutions :" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << x[i] << '\t';
        }
        exit(0);
        }
 
}
vector < vector < double>>  MatrixHesse(vector<double> x) {
    vector<vector<double>> Hesse =
    {
        {DF2DXi2(x,1), DF2DXiDXj(x,1,2) , DF2DXiDXj(x,1,3)},
        {DF2DXiDXj(x,2,1), DF2DXi2(x,2) , DF2DXiDXj(x,2,3)},
        {DF2DXiDXj(x,3,1), DF2DXiDXj(x,3,2) , DF2DXi2(x,3)}
    };
    return Hesse;
}
bool checkPositive(vector < double > x) {
    vector<vector<double>> Hesse = MatrixHesse(x);
    double minor1 = Hesse[0][0];
    double minor2 = Hesse[0][0] * Hesse[1][1] - Hesse[0][1] * Hesse[1][0];
    double minor3 =
        Hesse[0][0] * Hesse[1][1] * Hesse[2][2] + Hesse[0][1] * Hesse[1][2] * Hesse[2][0] + Hesse[0][2] * Hesse[1][0] * Hesse[2][1]
        -(Hesse[0][2] * Hesse[1][1] * Hesse[2][0] + Hesse[1][0] * Hesse[0][1] * Hesse[2][2] + Hesse[0][0] * Hesse[2][1] * Hesse[1][2]);
    if (minor1 > 0 && minor2 > 0 && minor3 > 0) {
        return true;
    }
    return false;
}
vector<vector<double>> reverseMatrix(vector<double> x)
{
    vector < vector < double>>det = { {0,0,0} , {0,0,0} ,{0,0,0} };
    vector < vector < double>> Hesse = MatrixHesse(x);
    double deter = Hesse[0][0] * Hesse[1][1] * Hesse[2][2] +
        Hesse[0][1] * Hesse[1][2] * Hesse[2][0] +
        Hesse[0][2] * Hesse[1][0] * Hesse[2][1] -
        Hesse[0][2] * Hesse[1][1] * Hesse[2][0] -
        Hesse[0][1] * Hesse[1][0] * Hesse[2][2] -
        Hesse[0][0] * Hesse[1][2] * Hesse[2][1];
    double deter_ = 1 / (fabs(deter));
    det[0][0] = Hesse[1][1] * Hesse[2][2] - Hesse[2][1] * Hesse[1][2];
    det[0][1] = Hesse[0][2] * Hesse[2][1] - Hesse[2][2] * Hesse[0][1];
    det[0][2] = Hesse[0][1] * Hesse[1][2] - Hesse[1][1] * Hesse[0][2];
    det[1][0] = Hesse[1][2] * Hesse[2][0] - Hesse[2][2] * Hesse[1][0];
    det[1][1] = Hesse[0][0] * Hesse[2][2] - Hesse[2][0] * Hesse[0][2];
    det[1][2] = Hesse[0][2] * Hesse[1][0] - Hesse[1][2] * Hesse[0][0];
    det[2][0] = Hesse[1][0] * Hesse[2][1] - Hesse[2][0] * Hesse[1][1];
    det[2][1] = Hesse[0][1] * Hesse[2][0] - Hesse[2][1] * Hesse[0][0];
    det[2][2] = Hesse[0][0] * Hesse[1][1] - Hesse[1][0] * Hesse[0][1];
    vector < vector < double>> reverse =
    {
     {det[0][0], det[0][1],det[0][2] },
     {det[1][0], det[1][1],det[1][2]},
     {det[2][0], det[2][1],det[2][2]}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            reverse[i][j] = reverse[i][j] * deter_;
        }
    }
    return reverse;
}
vector<double> multiply(vector<vector<double>> matrix, vector<double> vec) {
    vector<double> result;
    for (int i = 0; i < 3; i++) {
        double multiplyRes = 0;
        for (int j = 0; j < 3; j++) {
            multiplyRes += matrix[i][j] * vec[j];
        }
        result.push_back(multiplyRes);
    }
    return result;
}
void step7(vector<vector<double>>&x , int k) {
    vector < double > grad = gradient(x[k]);
    vector<vector<double>>reverseHesse = reverseMatrix(x[k]);
    vector<double> multi = multiply(reverseHesse, grad);
    vector<double> newX = { x[k][0] - multi[0],  x[k][1] - multi[1], x[k][2] - multi[2] };
    x.push_back(newX);

}
void step10(vector<vector<double>>& x, int& k, double eps, int kmax) {
    vector<double> diff = { x[k + 1][0] - x[k][0] , x[k + 1][1] - x[k][1] , x[k + 1][2] - x[k][2] };
    double norm = NormEvklid(diff);
    if (norm < eps) {
        cout << "Solutions :" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << x[k + 1][i] << '\t';
        }
        exit(0);
    }
    k++;
    if (k == kmax) {
        cout << "Solutions :" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << x[k][i] << '\t';
        }
        exit(0);
    }
}
void step5(vector<vector<double>>& x, int &k, double eps, int kmax) {
    if (checkPositive(x[k])) {
        step7(x, k);
        step10(x, k, eps, kmax);
    }
    else {
        double t_ = GoldenSearch(x[k],eps);
        vector<double>grad = gradient(x[k]);
        vector<double>newX = {x[k][0] - t_*grad[0] ,x[k][1]-t_*grad[1],x[k][2]-t_*grad[2]};
        x.push_back(newX);
        step10(x,k,eps,kmax);
    }
}
void Search() {
    int n = 3;
    int kmax;
    cout << "input a kmax = \n";
    cin >> kmax;
    int k = 0;
    double eps1, eps2;
    cout << "input a eps1 = \n";
    cin >> eps1;
    cout << "input a eps2 = \n";
    cin >> eps2;
    vector<double>x0 = { 0,0,0 };
    cout << "input a start values = \n";
    cout << "x1 = \n";
    cin >> x0[0];
    cout << "x2 = \n";
    cin >> x0[1];
    cout << "x3 = \n";
    cin >> x0[2];
    vector<vector<double>>x;
    x.push_back(x0);
    while (true) {
        step3(x[k],eps1);
        step5(x, k, eps2, kmax);
    }
}
int main()
{
    Search();
}