// Author: Nanako7_ix
// Created: 2025/03/25 22:37:40
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

array<int, 10> c = {3, 1, 2, 1, 0, 1, 0, 0, 0, 0};

void solve() {
    int n, ans = inf;
    cin >> n;
    array<int, 10> a {};
    auto check = [&]() {
        for(int i = 0; i < 10; ++i) {
            if(a[i] < c[i]) return false;
        }
        return true;
    };
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        a[x]++;
        if(check()) ans = min(ans, i);
    }
    if(ans == inf) {
        cout << 0 << endl;
    } else cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}