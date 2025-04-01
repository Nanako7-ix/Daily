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
    int n, ans = inf;
    cin >> n;
    map<int, vector<int>> pos;
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        pos[x].push_back(i);
    }
    for(auto [_, p] : pos) {
        if(p.size() < 2) continue;
        for(int i = 1; i < (int) p.size(); ++i) {
            ans = min(ans, p[i] - p[i - 1] + 1);
        }
    }
    cout << (ans == inf ? -1 : ans) << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}