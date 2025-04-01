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
    int n, m, Min = 0, Max = 0;
    cin >> n >> m;
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
        Min += a[i][0], Max += a[i][1];
    }

    if(Min > m || Max < m) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        int k = m - Min;
        for(int i = 1; i <= n; ++i) {
            int d = min(k, a[i][1] - a[i][0]);
            cout << a[i][0] + d << " \n"[i == n];
            k -= d;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}