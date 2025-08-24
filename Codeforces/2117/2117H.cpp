#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

constexpr int inf = 1E7;

struct Info {
    int Min, Max, ans, p;
    Info (int x = inf, int y = -inf, int pos = 0) {
        Min = x, Max = y, ans = Max - Min, p = pos;
    }
    void apply(int tag) {
        Min += tag, Max += tag;
    }
};

Info operator+(const Info& x, const Info& y) {
    Info res {};
    res.Min = min(x.Min, y.Min);
    res.Max = max(x.Max, y.Max);
    res.ans = max({ x.ans, y.ans, y.Max - x.Min });
    return res;
}

constexpr int N = 1000005;
mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
int tot, phi[N], siz[N], ls[N], rs[N], tag[N];
Info val[N], sum[N];

void pull(int u) {
    sum[u] = sum[ls[u]] + val[u] + sum[rs[u]];
    siz[u] = siz[ls[u]] + 1 + siz[rs[u]];
}

void apply(int u, int x) {
    if (x == 0) return;
    val[u].apply(x);
    sum[u].apply(x);
    tag[u] += x;
}

void push(int u) {
    if (ls[u]) apply(ls[u], tag[u]);
    if (rs[u]) apply(rs[u], tag[u]);
    tag[u] = 0;
}

int Node(Info x) {
    tot++;
    siz[tot] = 1;
    ls[tot] = rs[tot] = tag[tot] = 0;
    phi[tot] = rng();
    val[tot] = sum[tot] = x;
    return tot;
}

void split(int u, int p, int& x, int& y) {
    push(u);
    if (!(x = y = u)) return;
    if (val[u].p <= p) {
        split(rs[u], p, rs[u], y);
    } else {
        split(ls[u], p, x, ls[u]);
    }
    pull(u);
}

[[nodiscard]] int merge(int x, int y) {
    push(x), push(y);
    if (!x || !y) return x | y;
    if (phi[x] < phi[y]) {
        rs[x] = merge(rs[x], y);
        pull(x);
        return x;
    } else {
        ls[y] = merge(x, ls[y]);
        pull(y);
        return y;
    }
}

void Thephix() {
    tot = 0;
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    multiset<int> ans;
    for (int i = 1; i <= n; ++i) {
        ans.insert(sum[0].ans);
    }

    vector<int> root(n + 1);
    auto insert = [&](int p) {
        int k = a[p], x, y;
        split(root[k], p, x, y);
        if (y != 0) apply(y, 2);
        int node = Node(Info(2 * siz[x] - p + 1, 2 * siz[x] - p + 2, p));
        root[k] = merge(merge(x, node), y);
    };
    auto erase = [&](int p) {
        int k = a[p], x, y, z;
        split(root[k], p, y, z);
        split(y, p - 1, x, y);
        if (z != 0) apply(z, -2);
        root[k] = merge(x, z);
    };

    for (int i = 1; i <= n; ++i) {
        insert(i);
    }
    for (int i = 1; i <= n; ++i) {
        if (root[i] != 0) {
            ans.insert(sum[root[i]].ans);
        }
    }

    for (int i = 1; i <= q; ++i) {
        int p, x;
        cin >> p >> x;

        if (root[a[p]] != 0) {
            ans.extract(sum[root[a[p]]].ans);
        }
        erase(p);
        ans.insert(sum[root[a[p]]].ans);
        
        a[p] = x;
        
        if (root[a[p]] != 0) {
            ans.extract(sum[root[a[p]]].ans);
        }
        insert(p);
        ans.insert(sum[root[a[p]]].ans);
        
        cout << *rbegin(ans) / 2 << " \n"[i == q];
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}