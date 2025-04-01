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
    vector<i64> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; ++i) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end(), greater<i64> {});
    sort(b.begin() + 1, b.end(), greater<i64> {});
    for(int i = 1; i <= n; ++i) {
        a[i] += a[i - 1];
    }
    for(int i = 1; i <= m; ++i) {
        b[i] += b[i - 1];
    }

    i64 ans = 0, Max = 0;
    for(int i = 1; i <= n; ++i) {
        Max = max(Max, b[min(i, m)]);
        ans = max(ans, a[i] + Max);
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}