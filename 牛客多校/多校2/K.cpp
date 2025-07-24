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
    int n, k;
    string s;
    cin >> n >> k >> s;
    
    vector<array<int, 3>> tr(2);
    tr.reserve(1E6);
    for (int i = 0; i < n; ++i) {
        string t = s.substr(i);
        vector<int> fail(n - i);
        for (int j = 1, k = 0; j < n - i; ++j) {
            while (k != 0 && t[j] != t[k]) k = fail[k - 1];
            fail[j] = k += (t[j] == t[k]);
        }
        vector<int> ans(n - i);
        for (int j = 1, k = 0; j < n - i; ++j) {
            while (k != 0 && t[j] != t[k]) k = fail[k - 1];
            k += t[j] == t[k];
            while (k * 2 > j + 1) k = fail[k - 1];
            ans[j] = k;
        }
        for (int j = 0, p = 1; j < n - i; ++j) {
            int x = t[j] - '0';
            if (tr[p][x] == 0) {
                tr[p][x] = tr.size();
                tr.push_back({});
            }
            p = tr[p][x];
            tr[p][2] += ans[j] != 0 && j + 1 - 2 * ans[j] <= k;
        }
    }

    auto dfs = [&](auto&& dfs, int u) -> void {
        if (tr[u][0] != 0) dfs(dfs, tr[u][0]);
        if (tr[u][1] != 0) dfs(dfs, tr[u][1]);
        tr[u][2] += tr[tr[u][0]][2] + tr[tr[u][1]][2];
    };
    dfs(dfs, 1);

    auto siz = [&](int u) -> int {
        return tr[u][2];
    };

    auto cnt = [&](int u) -> int {
        return tr[u][2] - tr[tr[u][0]][2] - tr[tr[u][1]][2];
    };

    int q;
    cin >> q;
    i64 last = 0, total = tr[1][2];
    while (q--) {
        i64 x;
        cin >> x;
        x = (last + x - 1) % total + 1;
        last = 0;

        int p = 1;
        while (x > 0) {
            if (siz(tr[p][0]) >= x) {
                x -= cnt(tr[p][0]);
                p = tr[p][0];
                cout << 0;
                last = (last * 2 + 0) % 998244353;
            } else {
                x -= siz(tr[p][0]) + cnt(tr[p][1]);
                p = tr[p][1];
                cout << 1;
                last = (last * 2 + 1) % 998244353;
            }
        }
        cout << "\n";
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