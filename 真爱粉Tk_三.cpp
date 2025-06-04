/**
 * Author: Nanako7_ix
 * Created: 2025/04/20 19:36:39
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define int i64
#define debug(x) cerr << #x << " = " << x << "\n"
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
    vector<i64> cnt2(n + 1), cnt5(n + 1), a(n + 1);

    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        for (auto x : s) {
            if (x == '2') {
                cnt2[i]++;
            } else if (x == '5') {
                cnt5[i]++;
                a[i] += cnt2[i];
            }
        }
    }

    auto check = [&](i64 x) -> bool {
        int cnt = 0;
        i64 cur = 0, sum = 0;
        for (int i = 1; i <= n; ++i) {
            i64 get = a[i] + cur * cnt5[i];
            if (sum + get > x) {
                cnt++;
                sum = cur = 0;
                get = a[i];
            }
            sum += get, cur += cnt2[i];
        }
        return cnt < k;
    };

    i64 lo = *max_element(a.begin() + 1, a.end()), hi = INF;
    i64 res = -1;
    
    while (lo <= hi) {
        i64 mid = (lo + hi) >> 1;
        if (check(mid)) {
            hi = mid - 1, res = mid;
        } else lo = mid + 1;
    }

    assert(res != -1);
    cout << res << endl;
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}