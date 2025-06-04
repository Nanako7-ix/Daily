#include <bits/stdc++.h>
using namespace std;
int main () {
    int n= 20;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j) {
            if (i == j) cout << 0;
            if (i < j) cout << 100000;
            if (i > j) cout << 1;
            cout << " \n"[j == n];
        }
    }
}