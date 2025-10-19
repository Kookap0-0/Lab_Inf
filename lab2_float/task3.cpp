#include <iostream>
using namespace std;

int main() {
    cout<<fixed;
    cout.precision(1);

    float x = 1.0f;
    while (x<16777300) {
        float next = x + 1.0f;
        if (x>16777200) {
            cout << "x = " << x << ", x + 1 = " << next;
            cout << ", разница = " << (next - x) << endl;}
        x += 1.0f;
    }
    return 0;
}