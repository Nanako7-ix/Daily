/**
 * Author:  Nanako7_ix
 * Created: 2025/05/04 02:51:22
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
#define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> f(n + 1);
    for (int i = 1; i <= m; ++i) {
        int k; cin >> k;
        for (int j = 1; j <= k; ++j) {
            int x; cin >> x;
            f[x].push_back(i);
        }
    }

    i64 ans = INF;
    vector<int> cnt(m + 1);
    auto dfs = [&](auto dfs, int p, i64 res) -> void {
        if (p == n + 1) {
            if (*min_element(cnt.begin() + 1, cnt.end()) >= 2) {
                ans = min(ans, res);
            }
            return;
        }
        for (int i = 0; i < 3; ++i) {
            for (auto x : f[p]) {
                cnt[x] += i;
            }
            dfs(dfs, p + 1, res + i * a[p]);
            for (auto x : f[p]) {
                cnt[x] -= i;
            }
        }
    };
    dfs(dfs, 1, 0);

    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}