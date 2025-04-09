// Author: Nanako7_ix
// Created: 2025/04/09 20:01:34
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
    while(q--) {
        string op;
        cin >> op;
        if(op == "->") {
            int x, y;
            cin >> x >> y;
            x--, y--;

            i64 d = 0;
            for(int i = 0; i < n; ++i) {
                int down = x & 1;
                int right = y & 1;
                x >>= 1, y >>= 1;
                if(down == 0 && right == 0) {
                    d |= 0LL << (2 * i);
                } else if(down == 1 && right == 1) {
                    d |= 1LL << (2 * i);
                } else if(down == 1 && right == 0) {
                    d |= 2LL << (2 * i);
                } else {
                    d |= 3LL << (2 * i);
                }
            }
            cout << d + 1 << endl;
        } else {
            i64 d;
            cin >> d;
            d--;

            int x = 0, y = 0;
            for(int i = 0; i < n; ++i) {
                int msk = d & 3;
                d >>= 2;
                if(msk == 0) {
                    x |= 0LL << i;
                    y |= 0LL << i;
                } else if(msk == 1) {
                    x |= 1LL << i;
                    y |= 1LL << i;
                } else if(msk == 2) {
                    x |= 1LL << i;
                    y |= 0LL << i;
                } else {
                    x |= 0LL << i;
                    y |= 1LL << i;
                }
            }
            cout << x + 1 << ' ' << y + 1 << endl;
        }
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