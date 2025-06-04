/**
 * Author:  Nanako7_ix
 * Created: 2025/04/28 23:27:59
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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    array<vector<int>, 26> pos{};
    for (int i = 0; i < n; ++i) {
        pos[s[i] - 'a'].push_back(i);
    }

    vector<int> ans(n, inf);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < k; ++j) {
            auto it = lower_bound(pos[j].begin(), pos[j].end(), i + 1);
            if (it == pos[j].end()) {
                ans[i] = 1;
                break;
            }
            ans[i] = min(ans[i], ans[*it] + 1);
        }
    }

    int q; cin >> q;
    while (q--) {
        string t;
        cin >> t;

        int p = 0, ok = 0;
        for (auto x : t) {
            x -= 'a';
            auto it = lower_bound(pos[x].begin(), pos[x].end(), p);
            if (it == pos[x].end()) {
                cout << "0\n";
                ok = 1;
                break;
            }
            p = *it + 1;
        }

        if (ok) continue;

        cout << ans[p - 1] << endl;
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