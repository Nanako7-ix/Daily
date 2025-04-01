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
constexpr int N = 100;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<array<int, 2>>> dp(N + 1, vector<array<int, 2>> (N + 1, {-1, -1}));
    dp[0][0] = {0, 0};
    for(int i = 1; i <= n; ++i) {
        for(int j = N; j >= 0; --j) {
            for(int k = N; k >= 0; --k) {
                if(dp[j][k] != array<int, 2> {-1, -1}) continue;

                if(j - a[i] >= 0 && dp[j - a[i]][k] != array<int, 2> {-1, -1}) {
                    dp[j][k] = { j - a[i], k };
                }
                if(k - a[i] >= 0 && dp[j][k - a[i]] != array<int, 2> {-1, -1}) {
                    dp[j][k] = { j, k - a[i] };
                }
            }
        }
    }

    auto check = [&](int x, int y) {
        if(dp[x][y] == array<int, 2> {-1, -1}) return false;
        cout << "Yes\n";
        vector<int> l, r;
        while(x || y) {
            auto [tx, ty] = dp[x][y];
            if(tx == x) r.push_back(y - ty);
            if(ty == y) l.push_back(x - tx);
            x = tx, y = ty;
        }
        cout << l.size() << " " << r.size() << endl;
        for(auto _ : l) cout << _ << " ";
        cout << endl;
        for(auto _ : r) cout << _ << " ";
        cout << endl;
        return true;
    };

    for(int i = 1; i <= q; ++i) {
        int x, ok = 0;
        cin >> x;
        for(int j = 1; j * j <= x; ++j) {
            if(x % j == 0 && check(j, x / j)) {
                ok = 1; break;
            }
        }
        if(!ok) cout << "No\n";
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}