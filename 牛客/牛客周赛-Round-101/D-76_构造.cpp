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
    int n, m;
    cin >> n >> m;

    int ans = (1LL << (__lg(n) + 1)) - 1;
    if (m > ans || m % 2 == 0) {
        cout << "-1\n";
    } else {
        vector<int> vis(n + 1), a;
        for (int i = 1; i <= 20; ++i) {
            if (m >> i & 1) {
                a.push_back(1 << i);
                vis[1 << i] = 1;
            }
        }
        
        for (auto x : a) {
            cout << x << ' ';
        }
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) cout << i << ' ';
        }
        cout << "\n";

        if (*min_element(vis.begin() + 1, vis.end()) == 0) {
            cout << a.size() + 1 << "\n";
            for (int i = 1; i <= a.size(); ++i) {
                cout << i << ' ' << i << "\n";
            }
            cout << a.size() + 1 << ' ' << n << "\n";
        } else {
            cout << a.size() << "\n";
            for (int i = 1; i <= a.size(); ++i) {
                cout << i << ' ' << i << "\n";
            }
        }
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