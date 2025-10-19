#include <iostream>
#include <fstream>
//using namespace std;

const double ANALYTICAL = 1.0 / 3.0;

// Analyzed function
double f_double(double x) { return x * x; }
float f_float(float x) { return x * x; }

// Left rectangles
double left_rectangles_double(int n) {
    double h = 1.0 / n;
    double area = 0;
    for (int i = 0; i < n; i++) {
        double x = i * h;
        area += f_double(x) * h;
    }
    return area;
}
float left_rectangles_float(int n) {
    float h = 1.0 / n;
    float area = 0;
    for (int i = 0; i < n; i++) {
        float x = i * h;
        area += f_float(x) * h;
    }
    return area;
}

// Right rectangles 
double right_rectangles_double(int n) {
    double h = 1.0 / n;
    double area = 0;
    for (int i = 1; i <= n; i++) {
        double x = i * h;
        area += f_double(x) * h;
    }
    return area;
}
float right_rectangles_float(int n) {
    float h = 1.0 / n;
    float area = 0;
    for (int i = 1; i <= n; i++) {
        float x = i * h;
        area += f_float(x) * h;
    }
    return area;
}

// Mid rectangles
double mid_rectangles_double(int n) {
    double h = 1.0 / n;
    double area = 0;
    for (int i = 0; i < n; i++) {
        double x = (i + 0.5) * h;
        area += f_double(x) * h;
    }
    return area;
}
float mid_rectangles_float(int n) {
    float h = 1.0 / n;
    float area = 0;
    for (int i = 0; i < n; i++) {
        float x = (i + 0.5) * h;
        area += f_float(x) * h;
    }
    return area;
}

int main() {
    std::ofstream csv_file("numerical_integration.csv", std::ios::out);
    csv_file << "data_type,n,Left,Right,Mid" << std::endl;

    std::cout<<std::fixed;
    std::cout.precision(10);

    for (int n = 10; n <= 10000000; n += n/10) {
        double left_double = left_rectangles_double(n) - ANALYTICAL;
        double right_double = right_rectangles_double(n) - ANALYTICAL;
        double mid_double = mid_rectangles_double(n) - ANALYTICAL;
        csv_file <<"double"<< "," << n << "," << left_double << "," << right_double << "," << mid_double << std::endl;
        float left_float = left_rectangles_float(n) - ANALYTICAL;
        float right_float = right_rectangles_float(n) - ANALYTICAL;
        float mid_float = mid_rectangles_float(n) - ANALYTICAL;
        csv_file <<"float"<< "," << n << "," << left_float << "," << right_float << "," << mid_float << std::endl;
    }
   
    
    return 0;
}