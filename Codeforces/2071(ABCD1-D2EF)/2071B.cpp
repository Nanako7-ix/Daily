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

bool chk(i64 x) {
    i64 y = sqrt(x);
    if(y * y == x) return false;
    if((y + 1) * (y + 1) == x) return false;
    if((y - 1) * (y - 1) == x) return false;
    return 1;
}

void solve() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << "-1\n";
    } else {
        vector<int> a(n + 1);
        iota(a.begin(), a.end(), 0);
        for(i64 i = 1, now = 0; i <= n; ++i) {
            now += a[i];
            if(!chk(now)) {
                if(i == n) {
                    cout << "-1\n";
                    return;
                }
                swap(a[i], a[i + 1]);
                now -= a[i + 1];
                now += a[i];
            }
        }
        for(int i = 1; i <= n; ++i) {
            cout << a[i] << ' ';
        }
        cout << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}