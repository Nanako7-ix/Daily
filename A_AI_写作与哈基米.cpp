// Author: Nanako7_ix
// Created: 2025/03/29 16:17:11
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

bool check(i64 x) {
    if(x <= 1) return false;
    for(i64 i = 2; i * i <= x; ++i) {
        if(x % i == 0) return false;
    }
    return true;
}

void solve() {
    i64 a, b;
    cin >> a >> b;
    if(a == b + 1 && check(a + b)) {
        cout << "YES\n";
    } else cout << "NO\n";
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}