/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/15 22:03:26
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

// 从低位到高位 维护异或和并支持全局+1
template<int H>
struct Trie {
    int cnt = 0;
    vector<int> siz, sum;
    vector<array<int, 2>> ch;

    Trie(int n = 2e6) {
        siz.reserve(n), siz.assign(1, 0);
        sum.reserve(n), sum.assign(1, 0);
        ch.reserve(n), ch.assign(1, {});
    }

    int Node() {
        siz.push_back(0);
        sum.push_back(0);
        ch.push_back({});
        return ++cnt;
    }

    void pull(int u) {
        sum[u] = 0;
        int ls = ch[u][0], rs = ch[u][1];
        if(ls) sum[u] ^= sum[ls] << 1;
        if(rs) sum[u] ^= sum[rs] << 1 | (siz[rs] & 1);
    }

    void insert(const bitset<H>& x, int u = 0, int h = 0) {
        if(h != H) {
            if(!ch[u][x[0]]) {
                ch[u][x[0]] = Node();
            }
            insert(x >> 1, ch[u][x[0]], h + 1);
        }
        siz[u]++, pull(u);
    }

    void erase(const bitset<H>& x, int u = 0, int h = 0) {
        if(h != H) {
            erase(x >> 1, ch[u][x[0]], h + 1);
        }
        siz[u]--, pull(u);
    }

    void add(int u = 0) {
        swap(ch[u][0], ch[u][1]);
        if(ch[u][0]) add(ch[u][0]);
        pull(u);
    }

    int query() {
        return sum[0];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    vector tr(n + 1, Trie<20> (0));
    vector<int> fa(n + 1);
    auto dfs = [&](auto dfs, int u) -> void {
        for (auto v : adj[u]) {
            if (v == fa[u]) continue;
            fa[v] = u;
            tr[u].insert(a[v]);
            dfs(dfs, v);
        }
    }; dfs(dfs, 1);

    vector<int> add(n + 1);
    auto get = [&](int u) -> int {
        return a[u] + add[fa[u]];
    };

    for (int i = 1; i <= m; ++i) {
        int op, u;
        cin >> op >> u;
        if (op == 1) {
            tr[u].add();
            add[u]++;
            if (fa[u] != 0) {
                a[fa[u]]++;
                if (fa[fa[u]] != 0) {
                    tr[fa[fa[u]]].erase(get(fa[u]) - 1);
                    tr[fa[fa[u]]].insert(get(fa[u]));
                }
            }
        } else if (op == 2) {
            int v;
            cin >> v;
            a[u] -= v;
            if (fa[u] != 0) {
                tr[fa[u]].erase(get(u) + v);
                tr[fa[u]].insert(get(u));
            }
        } else {
            cout << (get(fa[u]) ^ tr[u].query()) << endl;
        }
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