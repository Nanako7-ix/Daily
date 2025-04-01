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

struct Treap {
    int n, rt = 0, idx = 1;
    vector<char> val;
    vector<int> ls, rs, siz, w, tag;
    mt19937 rng;
    Treap(string s) : rng(114) {
        n = s.size();
        val.assign(n + 1, 0);
        ls.assign(n + 1, 0);
        rs.assign(n + 1, 0);
        siz.assign(n + 1, 0);
        w.assign(n + 1, 0);
        tag.assign(n + 1, 0);
        for(int i = 0; i < n; ++i) {
            rt = merge(rt, add(s[i]));
        }
    }
    void push(int u) {
        if(tag[u]) {
            swap(ls[u], rs[u]);
            tag[ls[u]] ^= 1;
            tag[rs[u]] ^= 1;
            tag[u] = 0;
        }
    }
    void pull(int u) {
        siz[u] = siz[ls[u]] + 1 + siz[rs[u]];
    }
    int add(char x) {
        val[idx] = x, w[idx] = rng(), siz[idx] = 1;
        return idx++;
    }
    void split(int u, int k, int& x, int& y) {
        push(u);
        if(!(x = y = u)) return;
        if(siz[ls[x]] + 1 <= k) {
            split(rs[u], k - siz[ls[x]] - 1, rs[u], y);
        } else {
            split(ls[u], k, x, ls[u]);
        }
        pull(u);
    }
    int merge(int x, int y) {
        if(!x || !y) return x | y;
        push(x), push(y);
        if(w[x] > w[y]) {
            rs[x] = merge(rs[x], y);
            pull(x);
            return x;
        } else {
            ls[y] = merge(x, ls[y]);
            pull(y);
            return y;
        }
    }
    void reverse(int l, int r) {
        int t1, t2;
        split(rt, r, rt, t2);
        split(rt, l - 1, rt, t1);
        tag[t1] ^= 1;
        rt = merge(rt, t1);
        rt = merge(rt, t2);
    }
    void print(int u) {
        if(u == 0) return;
        push(u);
        print(ls[u]);
        cout << val[u];
        print(rs[u]);
    }
};

void solve() {
    int _, n;
    string s;
    cin >> _ >> n >> s;
    Treap tr(s);

    vector<int> l(n + 1), r(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> l[i];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> r[i];
    }
    int q; cin >> q;
    for(int i = 1; i <= q; ++i) {
        int x; cin >> x;
        int p = upper_bound(l.begin() + 1, l.end(), x) - l.begin() - 1;
        int a = min(x, r[p] + l[p] - x);
        int b = max(x, r[p] + l[p] - x);
        tr.reverse(a, b);
    }
    tr.print(tr.rt);
    cout << endl;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}