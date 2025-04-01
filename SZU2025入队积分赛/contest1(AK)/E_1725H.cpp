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
    bitset<100005> a;
    for(int i = 1; i <= n; ++i) {
        i64 x; cin >> x;
        a[i] = x * x % 3;
    }
    if(a.count() >= n / 2) {
        cout << 0 << endl;
        int cnt = a.count() - n / 2;
        for(int i = 1; i <= n; ++i) {
            if(a[i] == 1 && cnt) {
                a[i] = 0, cnt--;
            }
            cout << a[i];
        }
    } else {
        cout << 2 << endl;
        int cnt = n / 2 - a.count();
        for(int i = 1; i <= n; ++i) {
            if(a[i] == 0 && cnt) {
                a[i] = 1, cnt--;
            }
            cout << a[i];
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