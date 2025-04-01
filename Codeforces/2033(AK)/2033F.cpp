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
constexpr i64 Mod = 1000000007;

void solve() {
    i64 n, k;
    cin >> n >> k;
    n %= Mod;

    if(k == 1) {
        cout << n << endl;
        return;
    }

    i64 x = 1, y = 1, p = 3;
    while(1) {
        i64 z = (x + y) % k;
        if(z == 0) {
            cout << p * n % Mod << endl;
            return;
        }
        x = y, y = z, p++;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}