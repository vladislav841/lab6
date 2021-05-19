#include <iostream>
#include<cmath>
#include<vector>
#include<math.h>
using namespace std;
int index_d = 0;
int k = 0;
int i = 0;
//double eps = pow(10, -4);
vector<vector<float>>solutions;
float function(vector<float>x){
    return pow(x[0], 2) + 8*x[0]+ 5*pow(x[1], 2) + 7*pow(x[2], 2) + 119.0*x[2] + 531.75;
}
float FunctionOneVarible(vector<float> y, vector <float> d, float t) {
    vector<float> param = {y[0] + d[0] * t  , y[1] + d[1] * t ,y[2] + d[2] * t };
    return  function(param);
}
float GoldSearch(vector<float> y , vector<float> d,float eps) {
    float a0 = -100;
    float b0 = 100;
    double y0, z0;
  //  double eps = 0.00001;
    while (fabs(a0 - b0) > eps) {
        y0 = b0 - (b0 - a0) / ((1 + sqrt(5)) / 2);
        z0 = a0 + (b0 - a0) / ((1 + sqrt(5)) / 2);
        if (FunctionOneVarible(y,d,y0) > FunctionOneVarible(y,d,z0))
            a0 = y0;
        else
            b0 = z0;
    }
    return (b0 + a0) / 2;
}
float step2_a(vector<float> y, const vector<float> d,float eps) {
    float solution_t = GoldSearch(y, d , eps);
    return solution_t;
}
void step2_b(vector<vector<float>>&y , vector<vector<float>>d,float eps){
    float t_ = step2_a(y[y.size()-1], d[i], eps);
    vector<float> new_y = { 0,0,0 };
    for (int r = 0; r < 3; r++) {
        new_y[r] = y[y.size()-1][r] + d[i][r] * t_;
    }
    if (function(new_y) < function(y[y.size()-1])) {
        y.push_back(new_y);
    }
   /* else {
        y.push_back(y[0]);
    }*/
}
void step4(vector<vector<float>>&y, const vector<vector<float>>d, vector<vector<float>>&solutions,float eps) {
    bool isEqual = false;
    for (int i = 0; i < 3; i++) {
        if (y[y.size() - 1][i] == y[0][i]) {
            isEqual = true;
        }
        else {
            isEqual = false;
        }
    }
    if (isEqual) {
        solutions.push_back(y[y.size() - 1]);
    }
    else {
        i++;
        step2_b(y, d,eps);
    }
}
float Evklid(vector<float>x) {
    float result = 0;
    for (int i = 0; i < x.size(); i++) {
        result += x[i] * x[i];
    }
    return sqrt(result);
}
bool Rang(vector<vector<float>> d) {
    float deter = d[0][0] * d[1][1] * d[2][2] +
        d[0][1] * d[1][2] * d[2][0] +
        d[0][2] * d[1][0] * d[2][1] -
        d[0][2] * d[1][1] * d[2][0] -
        d[0][1] * d[1][0] * d[2][2] -
        d[0][0] * d[1][2] * d[2][1];
    if (deter == 0.0) {
        return false;
    }
    else {
        return true;
    }
}
void step7(vector<vector<float>>&y, vector<vector<float>>& d,float eps) {
    vector<vector<float>> new_d;
    vector<float> result = { 0,0,0 };
    for (int i = 0; i < 3; i++) {
        result[i] = y[y.size() - 1][i] - y[y.size() - 2][i];
    }
    new_d.push_back(result);
    new_d.push_back(d[1]);
    new_d.push_back(d[2]);
    new_d.push_back(result);
    if (Rang) {
        for (int i = 0; i < 4; i++) {
            d[i] = new_d[i];
            y[0] = y[y.size() - 1];
            k++;
        }
            i = 0;
            step2_b(y,d,eps);
    }
    else {
        y[0] = y[y.size() - 1];
        k++;
        i = 0;
        step2_b(y,d,eps);
    }
}
void step6(vector<vector<float>>&y, vector<vector<float>>&solutions , vector<vector<float>>d,float eps)
{
    //double eps = 0.001;
    bool isSmall = false;
    vector<float> result = { 0,0,0 };
    for (int i = 0; i < 3; i++) {
        result[i] = y[y.size() - 1][i] - y[y.size() - 2][i];
    }
    if (Evklid(result) < eps) {
        solutions.push_back(y[y.size() - 1]);
    }
    else {
          step7(y,d,eps);
    }
}
void step5(vector<vector<float>>&y , vector<vector<float>>&solutions, vector<vector<float>>d,float eps) {
    
    bool isEqual = false;
    for (int i = 0; i < 3; i++) {
        if (y[y.size() - 1][i] == y[1][i]) {
            isEqual = true;
        }
        else {
            isEqual = false;
        }
    }
    if (isEqual) {
        solutions.push_back(y[y.size() - 1]);
    }
    else {
        vector<vector<float>> solutions;
        step6(y,solutions,d,eps);
        if (solutions.size() > 0) {
            cout << "solutions in step 6= " << endl;
            for (int i = 0; i < 3; i++) {
                cout << solutions[0][i] << '\t'; 
            }
            cout << endl;
            cout << "func = " << function(solutions[0])<<endl;
            return;
        }
    }
}
void step3(vector<vector<float>>&y, vector<vector<float>>d,float eps) {
    while (i < 2) {
        i++;
        step2_b(y, d,eps);
    }
    if (i == 2) {
        vector<vector<float>> solutions;
        step4(y, d, solutions,eps);
        if (solutions.size() > 0) {
            cout << "solutions = " << endl;
            for (int i = 0; i < 3; i++) {
                cout << solutions[0][i] << '\t';
            }
            cout << endl;
            cout << "func = " << function(solutions[0]) << endl;
            return;
        }
    }
     if (i == 3) {
         vector<vector<float>> solutions;
         step5(y,solutions,d,eps);
         if (solutions.size() > 0) {
             cout << "solutions= " << endl;
             for (int i = 0; i < 3; i++) {
               
                 cout << solutions[0][i] << '\t';     
             }
             cout << endl;
             cout << "func = " << function(solutions[0]) << endl;
             return;
         }
     }
}
void Search(float eps) {
    vector<vector<float>> d = { {0,0,1} , { 1,0,0 } , { 0,1,0 }  ,{ 0,0,1 } };
    vector<vector<float>> y, x;
    vector<float> y0, x0 = { 0,0,0 };
    cout << "Input a start values = \n";
    cin >> x0[0] >> x0[1] >> x0[2];
    y0 = x0;
    y.push_back(y0);
    x.push_back(x0);
    step2_b(y, d,eps);
    step3(y, d,eps);
}
int main()
{
    float eps;
    cout << "input eps = " << endl;
    cin >> eps;
    Search(eps);
}