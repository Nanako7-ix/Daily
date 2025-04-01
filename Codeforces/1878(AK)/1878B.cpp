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
constexpr int N = 200000;

vector<int> a(N + 1);

void solve() {
    int n; cin >> n;
    for(int i = 1; i <= n; ++i) {
        cout << a[i] << " \n"[i == n];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);

    a[1] = 2, a[2] = 3;
    for(int i = 3; i <= N; ++i) {
        int P = a[i - 1] + a[i - 2];
        a[i] = a[i - 1] + 1;
        if(P % 3 == 0 && a[i] % (P / 3) == 0) {
            a[i]++;
        }
    }

    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}