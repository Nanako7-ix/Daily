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
    int _, n, m;
    cin >> _ >> n >> m;
    
    int x = _, y = _;
    for(int i = 1; i <= m; ++i) {
        ++x /= 2;
        if(x <= 1) break;
    }
    for(int i = 1; i <= n; ++i) {
        x /= 2;
        if(x == 0) break;
    }
    for(int i = 1; i <= n; ++i) {
        y /= 2;
        if(y == 0) break;
    }
    for(int i = 1; i <= m; ++i) {
        ++y /= 2;
        if(y <= 1) break;
    }
    cout << x << ' ' << y << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}