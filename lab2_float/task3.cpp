#include <iostream>
#include <cmath>
using namespace std;

int main() {
    cout<<fixed;
    cout.precision(1);

    float x = 1.0f;
    unsigned long long i = 0;
    while (true) {
        float next = x + 1.0f;

        if (i>16777200) {
            cout << "x = " << x << ", x + 1 = " << next;
            cout << ", разница = " << (next - x) << endl;
        }

        if (next == x) {
            cout << "x = " << x << endl;
            cout << "x + 1 = " << next << endl;
            cout << "Прибавление 1 не изменяет значение!" << endl;
            break;
            
        }

        x += 1.0f;
        i+=1;
    }
    
    return 0;
}