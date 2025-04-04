// Author: Nanako7_ix
// Created: 2025/04/04 00:12:07
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

map<pair<int, int>, i64> dp;
i64 zebra[31] = {
    0,
    1,
    5,
    21,
    85,
    341,
    1365,
    5461,
    21845,
    87381,
    349525,
    1398101,
    5592405,
    22369621,
    89478485,
    357913941,
    1431655765,
    5726623061,
    22906492245,
    91625968981,
    366503875925,
    1466015503701,
    5864062014805,
    23456248059221,
    93824992236885,
    375299968947541,
    1501199875790165,
    6004799503160661,
    24019198012642645,
    96076792050570581,
    384307168202282325
};

i64 solve(i64 n, i64 k) {
    i64 ans = 0;
    for(int i = 30; i > 0; --i) {
        if(n >= zebra[i]) {
            int x = n / zebra[i];
            n %= zebra[i];
            for(int j = 0; j < x; ++j) {
                if(k - j < 0) break;
                ans += dp[{i - 1, k - j}];
            }
            k -= x;
        }
        if(k < 0) break;
    }
    return ans + (k == 0);
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    int T = 1;
    cin >> T;

    dp[{0, 0}] = 1;
    for(int i = 1; i <= 30; ++i) {
        dp[{i, 4}] = 1;
        for(int j = 0; j <= 100; ++j) {
            dp[{i, j + 0}] += dp[{i - 1, j}];
            dp[{i, j + 1}] += dp[{i - 1, j}];
            dp[{i, j + 2}] += dp[{i - 1, j}];
            dp[{i, j + 3}] += dp[{i - 1, j}];
        }
    }

    while (T--) {
        i64 l, r, x;
        cin >> l >> r >> x;
        cout << solve(r, x) - solve(l - 1, x) << endl;
    }

    return 0;
}