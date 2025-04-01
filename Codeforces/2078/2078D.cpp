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
    vector<array<i64, 2>> add(n + 1, {0, 0}), mul(n + 1, {1, 1});
    vector<int> dir(n + 2);
    for(int i = 1; i <= n; ++i) {
        char op;
        cin >> op;
        if(op == '+') {
            cin >> add[i][0];
        } else cin >> mul[i][0];
        cin >> op;
        if(op == '+') {
            cin >> add[i][1];
        } else cin >> mul[i][1];
    }
    for(int i = n; i >= 1; --i) {
        if(mul[i][0] == mul[i][1]) {
            dir[i] = dir[i + 1];
        } else {
            dir[i] = mul[i][0] < mul[i][1];
        }
    }
    i64 x = 1, y = 1;
    for(int i = 1; i <= n; ++i) {
        i64 delt = 0;
        delt += x * (mul[i][0] - 1) + add[i][0];
        delt += y * (mul[i][1] - 1) + add[i][1];
        if(dir[i + 1] == 1) {
            y += delt;
        } else x += delt;
    }
    cout << x + y << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}