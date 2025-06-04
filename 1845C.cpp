/**
 * Author: Nanako7_ix
 * Created: 2025/04/17 14:28:06
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
    int n;
    string s, l, r;
    cin >> s >> n >> l >> r;
    
    vector<vector<int>> pos (10);
    for (int i = 0; i < (int) s.size(); ++i) {
        pos[s[i] - '0'].push_back(i);
    }

    for (int p = 0, x = -1; p < n; ++p) {
        int nxt = 0;
        for (int i = l[p] - '0'; i <= r[p] - '0'; ++i) {
            auto it = upper_bound(pos[i].begin(), pos[i].end(), x);
            if (it == pos[i].end()) {
                cout << "YES\n";
                return;
            }
            nxt = max(nxt, *it);
        }
        x = nxt;
    }

    cout << "NO\n";
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}