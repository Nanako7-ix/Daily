#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int inf = 1E9;

void Thephix() {
    int n;
    string s;
    cin >> n >> s;
    
    s = ' ' + s;
    for (int i = 1; i <= n; ++i) {
        s[i] -= '0';
    }

    vector<array<array<array<int, 4>, 2>, 2>> dp(n + 1);
    for (auto& val : dp[0] | views::join | views::join) {
        val = inf;
    }

    for (int p = 1; p <= n; ++p) {
        for (int last = 0; last <= 1; ++last) {
            for (int cnt = 0; cnt <= 3; ++cnt) {

            }
        }
    }
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