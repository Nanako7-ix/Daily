/**
 * Author:  Nanako7_ix
 * Created: 2025/04/29 22:22:55
 * 好想和 めぐる 一起打 xcpc 啊
 */
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

struct DSU {
    int n;
    vector<int> f, dep;
    vector<array<pair<int&, int>, 2>> stk;
    DSU (int n) {
        init(n);
    }
    void init(int n) {
        this -> n = n;
        f.resize(n + 1);
        dep.assign(n + 1, 1);
        std::iota(f.begin(), f.end(), 0);
    }
    int find (int x) {
        if (f[x] == x) return x;
        return find(f[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (dep[x] < dep[y]) swap(x, y);
        stk.push_back(array {
            pair<int&, int> {dep[x], dep[x]},
            pair<int&, int> {f[y], f[y]}
        });
        if (x == y) return false;
        dep[x] += dep[x] == dep[y];
        f[y] = x;
        return true;
    }
    void roll() {
        assert(!stk.empty());
        auto [ch1, ch2] = stk.back();
        ch1.first = ch1.second;
        ch2.first = ch2.second;
        stk.pop_back();
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    vector<array<int, 3>> a(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        if (a[i][0] == 1) {
            dsu.merge(a[i][1], a[i][2]);
        }
    }

    vector<char> ans;
    for (int i = m; i >= 1; --i) {
        if (a[i][0] == 1) {
            dsu.roll();
        } else {
            ans.push_back(dsu.find(a[i][1]) == dsu.find(a[i][2]) ? 'Y' : 'N');
        }
    }

    while (!ans.empty()) {
        cout << ans.back() << endl;
        ans.pop_back();
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}