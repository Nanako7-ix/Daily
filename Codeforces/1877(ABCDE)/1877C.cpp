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

int solve() {
    int n, m, k;
    cin >> n >> m >> k;

    if(k == 1) {
        return 1;
    }
    
    if(k == 2) {
        if(m <= n) return m;
        return n + (m / n - 1);
    }
    
    if(k == 3) {
        if(n == 1) return 0;
        if(m <= n) return 0;
        return m - n - (m / n - 1);
    }

    return 0;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) cout << solve() << endl;
    return 0;
}