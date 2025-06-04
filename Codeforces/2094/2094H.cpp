/**
 * Author: Nanako7_ix
 * Created: 2025/04/14 00:58:13
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
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    map<int, vector<int>> p;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }
    for(int i = 1; i <= q; ++i) {
        i64 k, l, r;
        cin >> k >> l >> r;
        while(k % a[l] == 0) k /= a[l];
        
        auto find = [&](int x, int begin) -> int {
            if(!p.contains(x)) return n + 1;
            auto it = upper_bound(p[x].begin(), p[x].end(), begin);
            return it == p[x].end() ? n + 1 : *it;
        };
        
        i64 ans = 0, now = l;
        while (true) {
            int fst = n + 1;
            for(i64 i = 1; i * i <= k; ++i) {
                if(k % i == 0) {
                    fst = min(fst, find(i, now));
                    fst = min(fst, find(k / i, now));
                }
            }
            if(fst > r) {
                ans += (r - now + 1) * k;
                break;
            } else {
                ans += (fst - now) * k;
                while(k % a[fst] == 0) k /= a[fst];
                now = fst;
            }
        }
        cout << ans << endl;
    }
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