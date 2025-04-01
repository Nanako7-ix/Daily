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
    i64 n, p;
    cin >> n >> p;
    vector<array<i64, 2>> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][1];
    }

    sort(a.begin(), a.end(), [](array<i64, 2> x, array<i64, 2> y) {
        if(x[1] == y[1]) {
            return x[0] > y[0];
        } return x[1] < y[1];
    });

    i64 ans = 0;
    priority_queue<i64, vector<i64>, greater<i64>> q;
    for(int i = 1; i <= n; ++i) {
        if(q.empty()) {
            ans += p;
        } else if(q.top() > p) {
            ans += (n - i + 1) * p;
            break;
        } else {
            ans += q.top();
            q.pop();
        }

        while(a[i][0] && q.size() < n - i) {
            q.push(a[i][1]);
            a[i][0]--;
        }
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