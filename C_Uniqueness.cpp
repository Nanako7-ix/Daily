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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    map<int, int> cnt;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int ans = -1;
    for(auto [val, _] : cnt) {
        if(_ == 1) ans = val;
    }
    
    if(ans == -1) {
        cout << "-1\n";
    } else {
        for(int i = 1; i <= n; ++i) {
            if(ans == a[i]) {
                cout << i << endl;
            }
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}