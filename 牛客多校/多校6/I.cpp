#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct SuffixAutomaton {
    static constexpr int N = 26;
    struct Node {
        int len;
        int link;
        std::array<int, N> next;
        Node() : len(), link(), next() {}
    };

    i64 substr;
    std::vector<Node> t;

    SuffixAutomaton () { init(); }

    void init() {
        t.assign(2, Node {});
        t[0].next.fill(1);
        t[0].len = -1;
        substr = 0;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }

        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }

        t[cur].link = extend(p, c);
        substr += t[cur].len - t[t[cur].link].len;
        return cur;
    }

    int len(int p) {
        return t[p].len;
    }

    int link(int p) {
        return t[p].link;
    }

    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int size() {
        return t.size();
    }

    i64 count () {
        return substr;
    }
};

#define ls (u << 1)
#define rs (u << 1 | 1)
template<typename Info, typename Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag>  tag;

    LazySegmentTree() = default;

    template<typename Func>
    LazySegmentTree(int n, Func&& op) { init(n, op); }

    template<typename Func>
    void init(int n, Func&& op) {
        this -> n = n;
        info.assign(4 << std::__lg(n), Info {});
        tag.assign(4 << std::__lg(n), Tag {});
        build(1, 1, n, op);
    }

    template<typename Func>
    void build(int u, int l, int r, Func&& op) {
        if (l == r) return void (info[u] = op(l));
        int m = (l + r) >> 1;
        build(ls, l, m, op);
        build(rs, m + 1, r, op);
    }

    void apply(int u, const Tag& v) {
        info[u].apply(v);
        tag[u].apply(v);
    }

    void pull(int u) {
        info[u] = info[ls] + info[rs];
    }

    void push(int u) {
        apply(ls, tag[u]);
        apply(rs, tag[u]);
        tag[u] = Tag{};
    }

    template<typename Func>
    void modify(int p, Func&& op) {
        modify(p, op, 1, 1, n);
    }

    void modify(int L, int R, const Tag& v, int u, int l, int r) {
        if (L <= l && r <= R) {
            apply(u, v);
            return;
        }
        push(u);
        int m = (l + r) >> 1;
        if (L <= m) modify(L, R, v, ls, l, m);
        if (R > m) modify(L, R, v, rs, m + 1, r);
        pull(u);
    }

    void modify(int l, int r, const Tag& v) {
        assert(l <= r);
        modify(l, r, v, 1, 1, n);
    }

    Info query(int L, int R, int u, int l, int r) {
        if (L <= l && r <= R) {
            return info[u];
        }
        push(u);
        int m = (l + r) >> 1;
        if (R <= m) {
            return query(L, R, ls, l, m);
        } else if (L > m) {
            return query(L, R, rs, m + 1, r);
        } else {
            return query(L, R, ls, l, m) + query(L, R, rs, m + 1, r);
        }
    }

    Info query(int l, int r) {
        assert(l <= r);
        return query(l, r, 1, 1, n);
    }
};
#undef ls
#undef rs

struct Info {
    int val;
    Info (int x = -1) {
        val = x;
    }
    void apply (const Info& v) {
        if (v.val == -1) return;
        val = max(v.val, val);
    }
};

Info operator+ (const Info& x, const Info& y) {
    return Info { max(x.val, y.val) };
}

void Thephix() {
    int n, q;
    string s;
    cin >> n >> q >> s;
    
    SuffixAutomaton sam;
    vector<int> a(n + 1);
    for (int i = 1, p = 1; i <= n; ++i) {
        a[i] = p = sam.extend(p, s[i - 1] - 'a');
    }

    int m = sam.size() - 1;
    vector<array<i64, 3>> dp(m + 1, { n, 1 });
    vector<vector<int>> adj(m + 1);
    for (int i = 2; i <= m; ++i) {
        adj[sam.link(i)].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        dp[a[i]][0] = dp[a[i]][1] = i;
    }
    auto dfs = [&](auto&& dfs, int u) -> void {
        dp[u][2] = sam.len(u);
        for (auto v : adj[u]) {
            dfs(dfs, v);
            dp[u][0] = min(dp[u][0], dp[v][0]);
            dp[u][1] = max(dp[u][1], dp[v][1]);
        }
    };
    dfs(dfs, 1);
    sort(dp.begin() + 2, dp.end());

    vector<array<int, 3>> query(q + 1);
    for (int i = 1; i <= q; ++i) {
        auto& [l, r, id] = query[i];
        cin >> l >> r;
        id = i;
    }

    sort(query.begin() + 1, query.end());
    vector<int> ans(q + 1);
    LazySegmentTree<Info, Info> seg1(n, [](int x) { return 0; });
    LazySegmentTree<Info, Info> seg2(n, [](int x) { return x; });
    for (int i = 1, j = 2; i <= q; ++i) {
        auto [l, r, id] = query[i];
        while (j <= m && dp[j][0] <= l) {
            auto [_, p, len] = dp[j++];
            seg1.modify(1, p - len + 1, len);
            seg2.modify(p - len + 1, p, p + 1);
        }
        int x = seg1.query(r, r).val;
        int y = seg2.query(r, r).val;
        ans[id] = max(x, y - r);
    }

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << "\n";
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}