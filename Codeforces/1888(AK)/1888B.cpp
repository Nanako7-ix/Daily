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
    int n, k;
    cin >> n >> k;

    if(k != 4) {
        int ans = inf;
        for(int i = 1; i <= n; ++i) {
            int x, res = 0;
            cin >> x;
            while(x % k) {
                x++, res++;
            }
            ans = min(ans, res);
        }
        cout << ans << endl;
    } else {
        array<int, 4> cnt{};
        for(int i = 1; i <= n; ++i) {
            int x; cin >> x;
            cnt[x % 4]++;
        }
        if(cnt[0]) {
            cout << 0 << endl;
        } else if(cnt[2] >= 2) {
            cout << 0 << endl;
        } else if(cnt[3]) {
            cout << 1 << endl;
        } else {
            cout << 2 - cnt[2] << endl;
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}