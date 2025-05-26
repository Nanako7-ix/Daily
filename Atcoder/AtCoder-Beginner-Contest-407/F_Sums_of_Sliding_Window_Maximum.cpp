/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/25 23:31:12
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
using f64 = double;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    map<int, vector<int>, greater<int>> pos;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }

    set<int> Break {0, n + 1};
    i64 ans = 0, d = 0;
    vector<i64> f(n + 1);

    auto modify = [&](i64 a1, i64 op, i64 val) {
        if (a1 == 0) return;
        ans += a1 * val * op;
        d -= val * op;
        f[a1] += val * op;
    };

    for (auto [val, p] : pos) {
        for (int i = 0; i < (int) p.size(); ++i) {
            auto it = Break.lower_bound(p[i]);
            int l = *prev(it) + 1, r = *it - 1;

            int j = lower_bound(p.begin(), p.end(), *it) - p.begin() - 1;
            modify(r - l + 1, 1, val);
            modify(r - p[j], -1, val);
            for (int k = i, lst = l; k <= j; lst = p[k++] + 1) {
                modify(p[k] - lst, -1, val);
                Break.insert(p[k]);
            }
            i = j;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans << endl;
        ans += d;
        d += f[i];
    }
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