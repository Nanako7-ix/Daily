#include <bits/stdc++.h>
using namespace std;

bool check (int n) {
    int t = sqrt(n);
    for (int i = t - 10; i <= t + 10; ++i) {
        if (i * i == n) {
            return true;
        }
    }
    return false;
}

int main () {
    int n;
    cin >> n;
    if (!check(n)) {
        cout << "No\n";
    } else {
        int sum = 0;
        while (n) {
            sum += n % 10;
            n /= 10;
        }
        if (check(sum)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}