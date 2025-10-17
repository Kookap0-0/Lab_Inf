#include <iostream>
using namespace std;

union fu {
 float f;
 unsigned int u;
};
void binary(unsigned int u) {
    for (int i = 31; i >= 0; i--) {
        cout << ((u >> i) & 1);
        if (i == 31 || i == 23) cout << " ";
    }
}

int main() {
    fu n;
    cin>>n.f;
    binary(n.u);
    return 0;
}