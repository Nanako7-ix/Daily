#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

#ifdef local
constexpr int maxn = 1000;
#else
constexpr int maxn = 1000000;
#endif

#define ls(u) ls[u]
#define rs(u) rs[u]
struct PersistentSegmentTree {
    int n, cnt;
    bitset<24 * maxn> info;
    vector<int> ls, rs, ver;

    PersistentSegmentTree(int n, int m) {
        this -> n = n;
        cnt = 0;
        int N = 24 * maxn;
        ver.assign(1 * maxn, 0);
        ls.assign(N, 0);
        rs.assign(N, 0);
        info = {};
    }

    void build(int& u, int l, int r) {
        if(u == 0) u = ++cnt;
        if(l == r) return;
        int m = (l + r) >> 1;
        build(ls(u), l, m);
        build(rs(u), m + 1, r);
    }

    bool modify(int p, int& u, int v, int l, int r) {
        u = ++cnt;
        ls(u) = ls(v), rs(u) = rs(v);
        if (l == r) {
            if(info.test(v)) {
                info.set(u);
                return false;
            }
            info.set(u);
            return true;
        }
        int m = (l + r) >> 1;
        if (p <= m) {
            return modify(p, ls(u), ls(v), l, m);
        } return modify(p, rs(u), rs(v), m + 1, r);
    }

    bool modify(int f, int u, int p) {
        return modify(p, ver[u], ver[f], 1, n);
    }
};
#undef ls
#undef rs

void solve() {
    int n, p = 0, cnt = 0;
    cin >> n;
    vector fa(n + 1, array<int, 11> {});
    vector<int> stk {0};
    vector<int> ans(n);
    PersistentSegmentTree seg(1 * maxn, n);

    for(int i = 1; i <= n; ++i) {
        char op;
        cin >> op;
        if(op == '+') {
            int x;
            cin >> x;
            cnt++;
            fa[cnt][0] = p, p = cnt;
            for(int k = 1; k < 11; ++k) {
                fa[p][k] = fa[fa[fa[fa[p][k - 1]][k - 1]][k - 1]][k - 1];
            }
            ans[p] = ans[fa[p][0]] + seg.modify(fa[p][0], p, x);
            stk.push_back(p);
        } else if(op == '-') {
            int x; cin >> x;
            for(int k = 10; k >= 0; --k) {
                while(x >= (1 << (k << 1))) {
                    // cout << "k = " << k << ' ' << x << ' ' << p << " -> ";
                    x -= 1 << (k << 1);
                    p = fa[p][k];
                    // cout << p << endl;
                }
            }
            // cout << p << endl;
            stk.push_back(p);
        } else if(op == '!') {
            stk.pop_back();
            p = stk.back();
            // cout << p << endl;
        } else {
            cout << ans[p] << endl;
        }
    }
    // cout << fa[4][0] << ' ' << fa[fa[4][0]][0] << endl;
}

int main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}