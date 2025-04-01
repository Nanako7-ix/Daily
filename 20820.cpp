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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int> (m + 1));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            char c; cin >> c;
            a[i][j] = c - '0';
        }
    }
    int r = 0, c = 0;
    for(int i = 1; i <= n; ++i) {
        int cnt = 0;
        for(int j = 1; j <= m; ++j) {
            cnt += a[i][j];
        }
        if(cnt & 1) r++;
    }
    for(int j = 1; j <= m; ++j) {
        int cnt = 0;
        for(int i = 1; i <= n; ++i) {
            cnt += a[i][j];
        }
        if(cnt & 1) c++;
    }
    cout << max(r, c) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}