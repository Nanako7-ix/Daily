// Author: Nanako7_ix
// Created: 2025/03/29 21:59:27
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
    int n;
    cin >> n;
    vector<vector<int>> p(n + 1);
    n <<= 1;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        p[a[i]].push_back(i);
    }
    int ans = 0;
    for(int i = 1; i <= n / 2; ++i) {
        int x = p[i][0], y = p[i][1];
        if(std::abs(x - y) == 1) {
            continue;
        }
        if(std::abs(x - y) == 2) {
            vector<int> t;
            for(int j = min(x, y) - 1; j <= max(x, y) + 1; ++j) {
                if(j >= 1 && j <= n && j != x && j != y) {
                    t.push_back(a[j]);
                }
            }
            sort(t.begin(), t.end());
            if(t.size() == 2) ans += t[0] == t[1];
            else ans += t[0] == t[1] || t[1] == t[2];
        } else {
            vector<int> l, r;
            if(x - 1 >= 1) l.push_back(a[x - 1]);
            if(x + 1 <= n) l.push_back(a[x + 1]);
            if(y - 1 >= 1) r.push_back(a[y - 1]);
            if(y + 1 <= n) r.push_back(a[y + 1]);
            for(auto _1 : l) {
                for(auto _2 : r) {
                    ans += _1 == _2;
                }
            }
        }
    }
    cout << ans / 2 << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}