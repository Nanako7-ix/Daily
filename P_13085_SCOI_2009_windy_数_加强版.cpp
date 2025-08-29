#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    string L, R;
    cin >> L >> R;
    reverse(L.begin(), L.end());
    reverse(R.begin(), R.end());
    while (L.size() != R.size()) {
        L.push_back('0');
    }

    vector dp (L.size(), vector (2, vector (2, vector<i64> (11, 0))));
    vector vis(L.size(), vector (2, vector (2, vector<i64> (11, 0))));
    auto dfs = [&](auto&& dfs, int p, bool liml, bool limr, int last) -> i64 {
        if (p == -1) return 1;
        if (vis[p][liml][limr][last + 1] == 0) {
            vis[p][liml][limr][last + 1] = 1;
            int l = liml ? L[p] - '0' : 0;
            int r = limr ? R[p] - '0' : 9;
            for (int i = l; i <= r; ++i) {
                if (last != -1 && abs(last - i) < 2) {
                    continue;
                }
                dp[p][liml][limr][last + 1] += dfs(
                    dfs,
                    p - 1,
                    liml && i == l,
                    limr && i == r,
                    last == -1 && i == 0 ? -1 : i
                );
            }
        }
        return dp[p][liml][limr][last + 1];
    };

    cout << dfs(dfs, L.size() - 1, 1, 1, -1) << "\n";
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}