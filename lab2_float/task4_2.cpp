#include <iostream>
#include <fstream>
using namespace std;

// f(x) = x^2
double f(double x) {
    return x * x;
}
double derivative_f(double x) {
    return 2 * x;
}
double antiderivative_f(double x) {
    return (x * x * x) / 3.0;
}

int main() {
    ofstream file_func("function_data.csv");
    file_func << "x,f(x),derivative,antiderivative"<<endl;
    for (int i = 0; i <= 150; i++) {
        double x = double(i)/25;
        file_func << x << "," << f(x) << "," << derivative_f(x) << "," << antiderivative_f(x) << "\n";
    }
    return 0;
}