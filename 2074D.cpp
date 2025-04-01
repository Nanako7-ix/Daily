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

i64 Sqrt(i64 x) {
    i64 t = sqrt(x);
    while(t * t > x) t--;
    while((t + 1) * (t + 1) <= x) t++;
    return t;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> x(n + 1), r(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> x[i];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> r[i];
    }
    map<int, i64> ans;
    for(int i = 1; i <= n; ++i) {
        for(int j = x[i] - r[i]; j <= x[i] + r[i]; ++j) {
            ans[j] = max(ans[j], Sqrt(r[i] * r[i] - abs(j - x[i]) * abs(j - x[i])));
        }
    }
    i64 sum = 0;
    for(auto [_, res] : ans) {
        sum += 2 * res + 1;
    }
    cout << sum << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}