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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 2; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    sort(b.begin() + 1, b.end());

    auto f = [&](i64 x) -> i64 {
        auto c = a;
        c[1] = x;
        sort(c.begin() + 1, c.end());
        int ans = 0;
        for(int i = 1; i <= n - ans; ++i) {
            while(i <= n - ans && c[i] >= b[i + ans]) {
                ans++;
            }
        }
        return ans;
    };
    
    i64 ans = f(1);
    int l = 2, r = m, res = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(f(mid) == ans + 1) {
            res = mid, r = mid - 1;
        } else l = mid + 1;
    }

    if(res == -1) {
        cout << ans * m << endl;
    } else {
        cout << ans * m + (m - res + 1) << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}