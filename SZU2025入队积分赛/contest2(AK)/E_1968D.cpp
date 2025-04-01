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
    int n, k, sx, sy;
    cin >> n >> k >> sx >> sy;
    vector<i64> a(n + 1), p(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<i64> get;
    vector<int> vis(n + 1);
    while(!vis[sx]) {
        get.push_back(a[sx]);
        vis[sx] = 1;
        sx = p[sx];
    }
    i64 ans1 = 0, sum = 0;
    for(int i = 0; i < min((int) get.size(), k); ++i) {
        ans1 = max(ans1, sum + (k - i) * get[i]);
        sum += get[i];
    }

    get.clear(), vis.assign(n + 1, 0), sum = 0;
    while(!vis[sy]) {
        get.push_back(a[sy]);
        vis[sy] = 1;
        sy = p[sy];
    }
    i64 ans2 = 0;
    for(int i = 0; i < min((int) get.size(), k); ++i) {
        ans2 = max(ans2, sum + (k - i) * get[i]);
        sum += get[i];
    }

    if(ans1 > ans2) cout << "Bodya\n";
    else if(ans1 == ans2) cout << "Draw\n";
    else cout << "Sasha\n";
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}