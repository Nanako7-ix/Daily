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

    bool merge(int x, int y) {
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
    string s;
    cin >> n >> m >> s;
    DSU dsu(n);
    for(int i = 1, j = n; i < j; ++i, --j) {
        dsu.merge(i, j);
    }
    for(int i = 1; i + m <= n; ++i) {
        dsu.merge(i, i + m);
    }
    vector cnt(n + 1, array<int, 26> {});
    for(int i = 1; i <= n; ++i) {
        cnt[dsu.find(i)][s[i - 1] - 'a']++;
    }
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        if(dsu.find(i) != i) continue;
        ans += dsu.size(i) - *max_element(cnt[i].begin(), cnt[i].end());
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