// Author: Nanako7_ix
// Created: 2025/03/30 20:31:09
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
    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;

    i64 ans = 0;
    for(int l = 1; l <= n; ++l) {
        for(int r = l; r <= n; ++r) {
            string t = s;
            for(int i = 1; i <= n; ++i) {
                if(t[i] != '?') continue;
                if(i < l || i > r) {
                    t[i] = 'o';
                } else t[i] = 'v';
            }

            i64 res = 0, x = 0, y = 0;
            for(int i = 1; i <= n; ++i) {
                y += t[i] == 'o';
            }
            for(int i = 1; i <= n; ++i) {
                if(t[i] == 'v') {
                    res += x * y;
                } else {
                    x++, y--;
                }
            }
            ans = max(ans, res);
        }
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}