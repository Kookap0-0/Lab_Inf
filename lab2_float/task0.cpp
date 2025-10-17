#include <iostream>
using namespace std;
int main() {
    unsigned int x;
    cin>>x;
    for (int i = 31; i >= 0; i--) {
        cout<< ((x & (1 << i)) ? 1 : 0);
    }
    return 0;
}