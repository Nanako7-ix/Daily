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

    int n = s.size();
    vector<int> p;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '#') p.push_back(i);
    }

    if (p.empty()) {
        s[0] = 'o';
        cout << s << "\n";
    } else {
        if (s[0] != '#') s[0] = 'o';
        if (s[n - 1] != '#') s[n - 1] = 'o';
        for (int i = 1; i < (int) p.size(); ++i) {
            if (p[i] != p[i - 1] + 1) {
                s[p[i - 1] + 1] = 'o';
            }
        }
        cout << s << "\n";
    }
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