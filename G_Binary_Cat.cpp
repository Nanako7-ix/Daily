#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr i64 inf = 1E18;

void Thephix() {
    int n;
    cin >> n;
    n += 2;

    // 怎么用 0-base，强烈谴责
    vector<array<i64, 3>> a(n + 1);
    vector fa(n + 1, vector<array<i64, 2>> (__lg(n) + 1));
    a[1] = { 0, 0, 1 };
    a[2] = { 0, 0, 1 };

    auto query = [&](int u) {
        i64 x;
        cin >> x;
        while (true) {
            for (int i = __lg(n); i >= 0; --i) {
                auto& [v, sum] = fa[u][i];
                if (v == 0) continue;
                if (x < sum + 1 || x > sum + a[v][2]) {
                    continue;
                }
                x -= sum, u = v;
            }
            if (u <= 2) {
                cout << u - 1 << "\n";
                return;
            }
            auto& [l, r, len] = a[u];
            if (a[l][2] >= x) {
                u = l;
            } else {
                u = r, x -= a[l][2];
            }
        }
    };
    
    for (int u = 3; u <= n; ++u) {
        auto& [l, r, len] = a[u];
        cin >> l >> r;
        l++, r++;
        if (a[l][2] >= inf) r = 1;
        len = a[l][2] + a[r][2];

        fa[u][0][0] = a[l][2] > a[r][2] ? l : r;
        fa[u][0][1] = a[l][2] > a[r][2] ? 0 : a[l][2];
        for (int i = 1; i <= __lg(n); ++i) {
            fa[u][i][0] = fa[fa[u][i - 1][0]][i - 1][0];
            fa[u][i][1] = fa[fa[u][i - 1][0]][i - 1][1] + fa[u][i - 1][1];
        }

        query(u);
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