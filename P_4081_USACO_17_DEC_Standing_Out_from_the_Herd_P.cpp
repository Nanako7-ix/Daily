#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct SAM {
    static constexpr int N = 26;
    struct Node {
        int len;
        int link;
        std::array<int, N> next;
        Node() : len(), link(), next() {}
    };

    i64 substr;
    std::vector<Node> t;

    SAM (int n = 0) {
        t.reserve(n);
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

    int extend(int p, char ch, char offset = 'a') {
        return extend(p, ch - offset);
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

void Thephix() {
    int n, len = 0;
    cin >> n;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        len += s[i].size();
    }

    SAM sam(len);
    vector<vector<int>> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        int m = s[i].size();
        p[i].resize(m + 1);
        p[i][0] = 1;
        for (int j = 1; j <= m; ++j) {
            p[i][j] = sam.extend(p[i][j - 1], s[i][j - 1]);
        }
    }

    int tot = sam.size() - 1;
    vector<vector<int>> adj(tot + 1);
    for (int i = 2; i <= tot; ++i) {
        adj[sam.link(i)].push_back(i);
    }

    vector<int> dp(tot + 1);
    for (int i = 1; i <= n; ++i) {
        int m = s[i].size();
        for (int j = 1; j <= m; ++j) {
            if (dp[p[i][j]] == 0) {
                dp[p[i][j]] = i;
            } else if (dp[p[i][j]] != i) {
                dp[p[i][j]] = -1;
            }
        }
    }

    auto dfs = [&](auto&& dfs, int u) -> void {
        for (auto v : adj[u]) {
            dfs(dfs, v);
            if (dp[u] == 0) {
                dp[u] = dp[v];
            } else if (dp[u] != dp[v]) {
                dp[u] = -1;
            }
        }
    };
    dfs(dfs, 1);

    vector<int> ans(n + 1);
    for (int i = 2; i <= tot; ++i) {
        if (dp[i] == -1) continue;
        ans[dp[i]] += sam.len(i) - sam.len(sam.link(i));
    }
    for (int i = 1; i <= n; ++i) {
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