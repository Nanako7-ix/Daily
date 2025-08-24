#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    string s;
    cin >> s;

    int n = s.size(), carry = 0, p = -1;
    reverse(s.begin(), s.end());
    for (int i = 0; i < n; ++i) {
        if (carry) {
            if (s[i] == '9') {
                s[i] = '0';
            } else {
                s[i]++, carry = 0;
            }
        }
        if (s[i] >= '5') {
            carry = 1;
            s[i] = '0';
            p = i;
        }
    }
    if (carry) s += '1';
    if (p != -1) {
        for (int i = 0; i <= p; ++i) {
            s[i] = '0';
        }
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}