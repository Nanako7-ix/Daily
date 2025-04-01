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
    i64 n, x, k;
    string s;
    cin >> n >> x >> k >> s;
    
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        a[i] = a[i - 1];
        if(s[i - 1] == 'L') {
            a[i]--;
        } else a[i]++;
    }

    int fstx = -1, fst0 = -1;
    for(int i = 1; i <= n; ++i) {
        if(fstx == -1 && a[i] == -x) {
            fstx = i;
        }
        if(fst0 == -1 && a[i] == 0) {
            fst0 = i;
        }
    }

    if(fstx == -1 || k < fstx) {
        cout << 0 << endl;
    } else {
        i64 ans = 1;
        k -= fstx;
        if(fst0 != -1) {
            ans += k / fst0;
        }
        cout << ans << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}