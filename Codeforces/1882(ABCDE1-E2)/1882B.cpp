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
    int n; cin >> n;
    vector<set<int>> a(n + 1);
    vector<int> p(60);
    for(int i = 1; i <= n; ++i) {
        int k; cin >> k;
        for(int j = 1; j <= k; ++j) {
            int x; cin >> x;
            a[i].insert(x);
            p[x] = 1;
        }
    }
    int ans = 0;
    for(int i = 1; i < 60; ++i) {
        if(p[i] == 0) continue;
        set<int> S;
        for(int j = 1; j <= n; j++) {
            if(a[j].contains(i)) continue;
            for(auto x : a[j]) {
                S.insert(x);
            }
        }
        ans = max<int>(ans, S.size());
    }
    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}