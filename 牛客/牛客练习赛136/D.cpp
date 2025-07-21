// Author: Nanako7_ix
// Created: 2025/04/03 19:33:59
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
    int n;
    i64 m;
    cin >> n >> m;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    auto check = [&](i64 x) -> int {
        i64 sum = 0;
        for(int i = 1; i <= n; ++i) {
            sum += max(a[i], a[i] ^ x);
            if(sum >= m) return true;
        }
        return false;
    };

    if(check(0)) {
        cout << "0\n";
        return;
    }

    for(int k = 0; k <= 60; ++k) {
        i64 res = 1LL << k;

        vector<i64> b;
        for(int i = 1; i <= n; ++i) {
            if((a[i] >> k & 1) == 0) {
                b.push_back(a[i]);
            }
        }

        for(int j = 0; j < k; ++j) {
            int add = 0;
            for(auto x : b) {
                if(x >> j & 1) {
                    add--;
                } else add++;
            }
            if(add > 0) res |= 1LL << j;
        }

        if(check(res)) {
            for(int j = k - 1; j >= 0; --j) {
                if((res >> j & 1) && check(res ^ (1LL << j))) {
                    res ^= 1LL << j;
                }
            }
            cout << res << endl;
            return;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}