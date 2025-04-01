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

class DSU {
private:
    int n, cnt;
    std::vector<int> f, siz;
public:
    DSU() = default;

    DSU(int n) { init(n); }

    void init(int n) {
        this -> n = n;
        cnt = n;
        f.resize(n + 1);
        siz.assign(n + 1, 1);
        std::iota(f.begin(), f.end(), 0);
    }

    int find(int x) {
        if(f[x] == x) return x;
        return f[x] = find(f[x]);
    }

    int merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return 0;
        cnt--, siz[x] += siz[y];
        return f[y] = x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }

    int count() const {
        return cnt;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> x(m + 1), y(m + 1), z(m + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= m; ++i) {
        cin >> x[i] >> y[i] >> z[i];
    }

    for(int k = 0; k < 30; ++k) {
        DSU dsu(2 * n);
        for(int i = 1; i <= m; ++i) {
            if(z[i] >> k & 1) {
                dsu.merge(x[i], y[i] + n);
                dsu.merge(x[i] + n, y[i]);
            } else {
                dsu.merge(x[i], y[i]);
                dsu.merge(x[i] + n, y[i] + n);
            }
        }
        for(int i = 1; i <= n; ++i) {
            if(dsu.same(i, i + n)) {
                cout << "-1\n";
                return;
            }
        }
        vector<vector<int>> p(n + 1);
        for(int i = 1; i <= 2 * n; ++i) {
            int root = dsu.find(i);
            if(root > n) continue;
            p[root].push_back(i);
        }
        for(int i = 1; i <= n; ++i) {
            if(p[i].empty()) continue;
            int c1 = 0, c2 = 0;
            for(auto x : p[i]) {
                if(x > n) {
                    c2++;
                } else c1++;
            }
            for(auto x : p[i]) {
                if(c1 >= c2 && x > n) {
                    a[x - n] |= 1 << k;
                }
                if(c1 < c2 && x <= n) {
                    a[x] |= 1 << k;
                }
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        cout << a[i] << ' ';
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}