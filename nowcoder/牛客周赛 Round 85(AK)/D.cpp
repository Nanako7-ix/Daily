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
    int n, ans = 0;
    string s;
    cin >> n >> s;

    map<array<int, 2>, int> vis;
    array<int, 2> cnt {};
    for(int i = s.size() - 1; i > 0; --i) {
        vis[cnt] = 1;
        cnt[s[i] - '0'] ^= 1;
        if(vis[cnt]) ans++;
    }
    cout << setpre(12) << 1.0 * ans / n << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}