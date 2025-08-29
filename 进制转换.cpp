#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

char f(int n) {
    if (n < 10) {
        return n + '0';
    } else {
        return (n - 10) + 'A';
    }
}

void Thephix() {
    int n, b, B;
    cin >> n >> b;
    B = abs(b);

    cout << n << "=";

    string s;
    while (n) {
        int x = ((n % B) + B) % B;
        s += f(x);
        n -= x;
        n /= b;
    }

    reverse(s.begin(), s.end());
    cout << s << "(base" << b << ")\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}