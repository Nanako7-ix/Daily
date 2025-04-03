// Author: Nanako7_ix
// Created: 2025/04/03 19:11:25
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
    i64 n, m;
    string s;
    cin >> n >> m >> s;
    vector<int> a(n + 1), nxt(n + 1, -1);
    s = ' ' + s;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int lst = 1;
    for(int i = 2; i <= n; ++i) {
        if(s[i] != s[lst]) {
            for(int j = lst; j < i; ++j) {
                nxt[j] = i;
            }
            sort(a.begin() + lst, a.begin() + i);
            lst = i;
        }
    }
    sort(a.begin() + lst, a.end());

    for(int i = 1; i <= n; ++i) {
        cout << s[i];
        if(nxt[i] <= n && s[i] < s[nxt[i]] && m >= a[i]) {
            cout << s[i];
            m -= a[i];
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}