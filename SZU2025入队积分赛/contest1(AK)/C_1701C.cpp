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
    int n, m;
    cin >> n >> m;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= m; ++i) {
        int x; cin >> x;
        cnt[x]++;
    }

    auto chk = [&](int x) -> bool {
        int res = 0;
        for(int i = 1; i <= n; ++i) {
            if(cnt[i] <= x) {
                res += cnt[i];
                res += (x - cnt[i]) / 2;
            } else {
                res += x;
            }
            if(res >= m) return true;
        }
        return false;
    };

    int l = 1, r = 2 * m, res = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(chk(mid)) {
            res = mid, r = mid - 1;
        } else l = mid + 1;
    }
    cout << res << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}