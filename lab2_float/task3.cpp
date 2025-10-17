#include <iostream>
using namespace std;

void binary(unsigned int u) {
    for (int i = 31; i >= 0; i--) {
        cout << ((u >> i) & 1);
        if (i == 31 || i == 23) cout << " ";
    }
}

union fu {
    float f;
    unsigned int u;
};

int main() {
    cout << fixed;
    cout.precision(1);
    fu num;
    unsigned long long int_number = 1;
    for (int i = 0; i <= 15; i++) {
        num.f = (float)int_number;
        cout << "10^" << i << " = " << num.f << " = ";
        binary(num.u);
        cout << endl;
        int_number *= 10;
    }
    
    return 0;
}