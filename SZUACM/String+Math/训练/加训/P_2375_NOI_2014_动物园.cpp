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
 * Created: 2025/05/21 15:26:54
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
constexpr int Mod = 1000000007;

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    vector<int> fail(n), dep(n + 1);
    dep[1] = 1;
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) {
            j = fail[j - 1];
        }
        fail[i] = j += (s[i] == s[j]);
        dep[i + 1] = dep[fail[i]] + 1;
    }
    
    vector<int> ans(n);
    for (int i = 1, j = 0; i < n; ++i) {
        while (j && s[i] != s[j]) {
            j = fail[j - 1];
        }
        j += s[i] == s[j];
        while (j * 2 > i + 1) j = fail[j - 1];
        ans[i] = dep[j];
    }
    /*
    利用 KMP 的 fail 指针建树，容易想到一个倍增的 nlogn 的解法，但是会 TLE
        vector<vector<int>> adj(n + 2);
        for (int i = 0; i < n; ++i) {
            adj[i + 2].push_back(fail[i] + 1);
            adj[fail[i] + 1].push_back(i + 2);
        }
        n++;
        vector<int> dep(n + 1);
        vector fa(n + 1, vector<int> (__lg(n) + 1));
        auto dfs = [&](auto&& dfs, int u) -> void {
            for (auto v : adj[u]) {
                if (v == fa[u][0]) continue;
                fa[v][0] = u;
                dep[v] = dep[u] + 1;
                dfs(dfs, v);
            }
        };
        dfs(dfs, 1);

        for (int i = 1; i <= __lg(n); ++i) {
            for (int u = 1; u <= n; ++u) {
                fa[u][i] = fa[fa[u][i - 1]][i - 1];
            }
        }

        vector<int> ans(n + 1);
        for (int u = 2; u <= n; ++u) {
            int v = u;
            for (int i = __lg(dep[u]); i >= 0; --i) {
                if ((fa[v][i] - 1) * 2 > u - 1) {
                    v = fa[v][i];
                }
            }
            v = fa[v][0];
            ans[u] = dep[v];
        }
    */

    i64 mul = 1;
    for (int i = 0; i < n; ++i) {
        mul = mul * (ans[i] + 1) % Mod;
    } 
    cout << mul << endl;
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