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
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    if(k == n - 1) {
        cout << accumulate(a.begin() + 1, a.end(), 0ll) << endl;
        return;
    }

    if(k == 1) {
        i64 ans = 0, Max = *max_element(a.begin() + 1, a.end());
        if(Max == a[1]) {
            cout << Max + *max_element(a.begin() + 2, a.end()) << endl;
        } else if(Max == a[n]) {
            cout << Max + *max_element(a.begin() + 1, a.end() - 1) << endl;
        } else {
            cout << Max + max(a[1], a[n]) << endl;
        }
        return;
    }

    sort(a.begin() + 1, a.end());
    
    i64 ans = 0;
    for(int i = n - k; i <= n; ++i) {
        ans += a[i];
    }

    cout << ans << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}