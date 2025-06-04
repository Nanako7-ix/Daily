/**
 * Author: Nanako7_ix
 * Created: 2025/04/13 23:47:56
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

namespace treap {
    constexpr int maxn = 2e6;
    struct Info {
        i64 val;
        Info(i64 x = 0) { val = x; }
    };

    auto operator<=>(Info x, Info y) {
        return x.val <=> y.val;
    }
    Info operator+(Info x, Info y) {
        return Info(x.val + y.val);
    }

    mt19937 sj(0);
    Info val[maxn];
    Info info[maxn];
    int siz[maxn], key[maxn], ls[maxn], rs[maxn], fa[maxn];
    int rev[maxn];
    int cnt = 1;

    void init() {
        cnt = 1;
        val[0] = info[0] = Info(0);
    }
    int add(Info x) {
        info[cnt] = val[cnt] = x;
        key[cnt] = (int) sj();
        siz[cnt] = 1, ls[cnt] = 0, rs[cnt] = 0, fa[cnt] = 0;
        rev[cnt] = 0;
        return cnt++;
    }
    void pull(int u) {
        siz[u] = siz[ls[u]] + 1 + siz[rs[u]];
        info[u] = info[ls[u]] + val[u] + info[rs[u]];
    }
    void push(int u) {
        if(rev[u]) {
            swap(ls[u], rs[u]);
            rev[ls[u]] ^= 1, rev[rs[u]] ^= 1;
            rev[u] = 0;
        }
    }
    void split_val(int u, Info k, int& x, int& y, int fx = 0, int fy = 0) {
        push(u);
        if(!(x = y = u)) return;
        if(val[u] <= k) {
            fa[u] = fx;
            split_val(rs[u], k, rs[u], y, u, fy);
        } else {
            fa[u] = fy;
            split_val(ls[u], k, x, ls[u], fx, u);
        }
        pull(u);
    }
    void split_rnk(int u, int k, int& x, int& y, int fx = 0, int fy = 0) {
        push(u);
        if(!(x = y = u)) return;
        if(siz[ls[u]] + 1 <= k) {
            fa[u] = fx;
            split_rnk(rs[u], k - siz[ls[u]] - 1, rs[u], y, u, fy);
        } else {
            fa[u] = fy;
            split_rnk(ls[u], k, x, ls[u], fx, u);
        }
        pull(u);
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        push(x), push(y);
        if(key[x] < key[y]) {
            rs[x] = merge(rs[x], y);
            if(rs[x]) fa[rs[x]] = x;
            pull(x);
            return x;
        } else {
            ls[y] = merge(x, ls[y]);
            if(ls[y]) fa[ls[y]] = y;
            pull(y);
            return y;
        }
    }
    template<class... Args>
    [[nodiscard]] int mergeall(Args... args) {
        int rt = 0;
        ((rt = merge(rt, args)), ...);
        return rt;
    }
    template<class T>
    int findleft(int rt, T&& f) {
        if(!f(info[rt])) return inf;
        int u = rt, k = 0;
        while(1) {
            push(u);
            if (ls[u] && f(info[ls[u]])) {
                u = ls[u];
            } else if(f(val[u])) {
                return k + siz[ls[u]] + 1;
            } else {
                k += siz[ls[u]] + 1, u = rs[u];
            }
        }
    }
    template<class T>
    int findright(int rt, T&& f) {
        if(!f(info[rt])) return -inf;
        int u = rt, k = 0;
        while(1) {
            push(u);
            if (rs[u] && f(info[rs[u]])) {
                k += siz[ls[u]] + 1, u = rs[u];
            } else if(f(val[u])) {
                return k + siz[ls[u]] + 1;
            } else {
                u = ls[u];
            }
        }
    }
    int rank(int x) {
        auto dfs = [&](auto dfs, int u) -> void {
            if(fa[u]) dfs(dfs, fa[u]);
            push(u);
        }; dfs(dfs, x);
        int res = siz[ls[x]] + 1;
        for(int u = x; fa[u]; u = fa[u])
            if(u == rs[fa[u]])
                res += siz[ls[fa[u]]] + 1;
        return res;
    }
    int find(int x) {
        while(fa[x]) x = fa[x];
        return x;
    }
}

void solve() {
    treap::init();
    int n = 0, rt = 0, q;
    cin >> q;
    i64 ans = 0;
    while(q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int t1, t2;
            treap::split_rnk(rt, n - 1, t1, t2);
            ans -= (n - 1) * treap::val[t2].val;
            ans += treap::info[t1].val;
            rt = treap::mergeall(t2, t1);
        } else if (op == 2) {
            i128 sum = treap::info[rt].val;
            treap::rev[rt] ^= 1;
            sum *= n + 1;
            ans = sum - ans;
        } else {
            i64 k; cin >> k;
            ans += ++n * k;
            rt = treap::mergeall(rt, treap::add(k));
        }
        cout << ans << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
    
    int T = 1;
    cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}