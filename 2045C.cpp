#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
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
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    array<int, 26> ps {}, pt {};
    for(int i = 1; i < n; ++i) {
        if(ps[s[i] - 'a'] == 0) {
            ps[s[i] - 'a'] = i + 1;
        }
    }
    for(int i = m - 1; i >= 0; --i) {
        if(pt[t[i] - 'a'] == 0) {
            pt[t[i] - 'a'] = m - i - 1;
        }
    }
    int ans = inf, x, y;
    for(int i = 0; i < 26; ++i) {
        if(ps[i] == 0 || pt[i] == 0) continue;
        if(ps[i] + pt[i] < ans) {
            ans = ps[i] + pt[i];
            x = ps[i], y = pt[i];
        }
    }

    if(ans == inf) {
        cout << "-1\n";
    } else {
        cout << s.substr(0, x) << t.substr(m - y) << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}