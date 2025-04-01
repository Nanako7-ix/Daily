// Author: Nanako7_ix
// Created: 2025/03/29 22:37:59
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
    string s, t;
    cin >> n >> s >> t;
    int odd = 0, even = 0;
    for(int i = 0; i < n; ++i) {
        if(t[i] == '1') continue;
        if(i & 1) odd++;
        else even++;
    }
    for(int i = 0; i < n; ++i) {
        if(s[i] == '0') continue;
        if(i & 1) even--;
        else odd--;
    }
    if(odd >= 0 && even >= 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}