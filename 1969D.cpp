/**
 * Author: Nanako7_ix
 * Created: 2025/04/11 21:15:53
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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    i64 sum = 0;
    for(int i = 1; i <= n; ++i) {
        cin >> b[i];
        sum += max(0, b[i] - a[i]);
    }

    i64 ans = k == 0 ? sum : 0;
    vector<int> id(n + 1);
    ranges::iota(id, 0);
    ranges::sort(id, [&](int x, int y) {
        return b[x] < b[y];
    });

    priority_queue<i64> q;
    for(int i = n; i >= 1; --i) {
        q.push(a[id[i]]), sum -= a[id[i]];
        sum -= max(0, b[id[i]] - a[id[i]]);
        if((int) q.size() > k) {
            sum += q.top(), q.pop();
        }
        if((int) q.size() == k) {
            ans = max(ans, sum);
        }
    }
    cout << ans << endl;
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