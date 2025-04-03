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
#define int i64
void solve() {
    i64 t;
    cin >> t;
    i64 p = sqrt(t);
    while(p * p >= t) p--;
    if(p % 2 == 0) p--;
    t -= p * p;
    
    int max = (p + 1) / 2;
    p = 2 * max;

    if(t <= p) {
        cout << max << ' ' << max - t << endl;
    } else if(t <= 2 * p) {
        t -= p;
        cout << max - t << ' ' << -max << endl;
    } else if(t <= 3 * p) {
        t -= 2 * p;
        cout << -max << ' ' << t - max << endl;
    } else if(t <= 4 * p) {
        t -= 3 * p;
        cout << t - max << ' ' << max << endl;
    } else {
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}