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
    vector<array<int, 2>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    sort(a.begin() + 1, a.end(), [](array<int, 2> x, array<int, 2> y) {
        int Min1 = min(x[0], x[1]), Min2 = min(y[0], y[1]);
        int Max1 = max(x[0], x[1]), Max2 = max(y[0], y[1]);
        if(Min1 != Min2) {
            return Min1 < Min2;
        } return Max1 < Max2;
    });
    for(int i = 1; i <= n; ++i) {
        cout << a[i][0] << ' ' << a[i][1] << " \n"[i == n];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}