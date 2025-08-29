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
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] == '#') {
            p.push_back(i);
        }
    }

    for (int i = 0; i < (int) p.size(); i += 2) {
        cout << p[i] << "," << p[i + 1] << "\n";
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