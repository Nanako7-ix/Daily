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
    vector<i64> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    i64 sum = 0;
    vector<i64> b(2 * n + 2);
    for(int i = 1; i <= n - 1; ++i) {
        sum += a[i];
        b[i * 2] = a[i];
    }
    for(int i = n; i <= 2 * n; ++i) {
        sum -= a[i];
        b[2 * (i - n + 1) - 1] = a[i];
    }
    b[2 * n] = -sum;
    for(int i = 1; i <= 2 * n + 1; ++i) {
        cout << b[i] << ' ';
    }
    cout << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}