/**
 * Author: Nanako7_ix
 * Created: 2025/04/24 00:40:06
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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] > m) {
            cout << "NO\n";
            return;
        }
    }

    if (m > n) {
        map<int, int> vis;
        for (int i = 1; i <= n; ++i) {
            if (vis[a[i]]) {
                cout << "NO\n";
                return;
            }
            vis[a[i]] = 1;
        }
        cout << "YES\n";
        return;
    }

    vector<int> nxt(n + 1), cnt(m + 1);
    iota(nxt.begin(), nxt.end(), 0);

    for (int l = 1, r = 0; l <= n; ++l) {
        while (r <= n && cnt.min == 0) {
            cnt[a[r]]++;
            ++r;
        }
        if (cnt.min == 0) break;
        nxt[l] = r;
        cnt[a[l]]--;
    }

    ranges::fill(cnt, 0);
    int p = n;
    while (!cnt[p]) {
        cnt[p--]++;
    }

    ranges::fill(cnt, 0);
    for (int i = 1; i <= n; ++i) {

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