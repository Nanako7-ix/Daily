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
 * Created: 2025/05/17 15:55:38
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

template<int H>
struct Trie {
    int cnt = 0;
    vector<int> siz;
    vector<array<int, 2>> ch;

    Trie(int n = 2e6) {
        siz.reserve(n), siz.assign(1, 0);
        ch.reserve(n), ch.assign(1, {});
    }

    int Node() {
        ch.push_back({});
        siz.push_back(0);
        return ++cnt;
    }

    void modify(const bitset<H>& x) {
        int p = 0;
        siz[0]++;
        for(int i = H - 1; i >= 0; --i) {
            if(!ch[p][x[i]]) {
                ch[p][x[i]] = Node();
            }
            siz[p = ch[p][x[i]]]++;
        }
    }

    u64 max(bitset<H> x) {
        for(int i = H - 1, p = 0; i >= 0; --i) {
            if(ch[p][!x[i]] && siz[ch[p][!x[i]]]) {
                p = ch[p][!x[i]], x[i] = 1;
            } else p = ch[p][x[i]], x[i] = 0;
        }
        return x.to_ullong();
    }

    u64 min(bitset<H> x) {
        for(int i = H - 1, p = 0; i >= 0; --i) {
            if(ch[p][x[i]] && siz[ch[p][x[i]]]) {
                p = ch[p][x[i]], x[i] = 0;
            } else p = ch[p][!x[i]], x[i] = 1;
        }
        return x.to_ullong();
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<array<int, 2>>> adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        for (auto [v, w] : adj[u]) {
            if (v == fa) continue;
            a[v] = a[u] ^ w;
            dfs(dfs, v, u);
        }
    };
    dfs(dfs, 1, 0);

    u64 ans = 0;
    Trie<31> tr;
    for (int i = 1; i <= n; ++i) {
        tr.modify(a[i]);
        ans = max(ans, tr.max(a[i]));
    }
    cout << ans << endl;
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