#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

vector<vector<int>> fac;

void Thephix() {
    int n, m, x, ok = 0;
    cin >> n >> m >> x;
    vector<int> a(n + 1);
    
    auto dfs = [&](auto&& dfs, int p, int sum) -> void {
        if (sum + n - p + 1 > x) return;
        if (sum + (n - p + 1) * a[p - 1] < x) return;
        if (p == n + 1) {
            if (sum == x) {
                ok = 1;
                for (int i = 1; i <= n; ++i) {
                    cout << a[i] << " \n"[i == n];
                }
            }
            return;
        }
        for (auto& x : fac[a[p - 1]]) {
            a[p] = x;
            dfs(dfs, p + 1, sum + x);
            if (ok) return;
        }
    };
    
    for (int i = 1; !ok && i <= m; ++i) {
        a[1] = i;
        dfs(dfs, 2, i);
    }

    if (!ok) cout << "-1\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    constexpr int N = 50;
    fac.assign(N + 1, {});
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (i % j == 0) {
                fac[i].push_back(j);
            }
        }
    }

    while (T--) {
        Thephix();
    }

    return 0;
}