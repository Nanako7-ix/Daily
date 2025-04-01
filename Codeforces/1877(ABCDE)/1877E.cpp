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

// 在基环树上的一个构造
// 0 的出点一定是 1
// 没有 0 入点的点一定是 0
// 对所有的 0 进行构造即可 (真吗?)

void solve() {
    int n; cin >> n;
    vector<int> p(n + 1), deg(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> p[i];
        deg[p[i]]++;
    }

    vector<int> cnt(n + 1), dp(n + 1, -1);
    queue<int> q;
    for(int i = 1; i <= n; ++i) {
        if(deg[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int u = q.front(), v = p[u];
        q.pop();
        
        if(cnt[u] == 0) {
            dp[u] = 0, cnt[v]++;
        } else dp[u] = 1;

        if(--deg[v] == 0) {
            q.push(v);
        }
    }

    vector<int> vis(n + 1);
    for(int i = 1; i <= n; ++i) {
        if(dp[i] != -1) continue;
        int fl = 0;
        vector<array<int, 2>> cir;
        for(int u = i; !vis[u]; u = p[u]) {
            vis[u] = 1;
            if(cnt[u]) dp[u] = 1;
            cir.push_back({u, dp[u]});
            if(dp[u] != -1) fl = 1;
        }

        if(fl == 0) {
            if(cir.size() & 1) {
                cout << "-1\n";
                return;
            } else {
                for(int j = 0; j < (int) cir.size(); ++j) {
                    dp[cir[j][0]] = j & 1;
                }
            }
        } else {
            for(int j = 0; j < 2 * cir.size(); ++j) {
                int u = cir[j % cir.size()][0];
                int v = cir[(j + 1) % cir.size()][0];
                if(dp[u] == -1) continue;
                if(dp[v] == -1) dp[v] = dp[u] ^ 1;
                else if(dp[u] == 0 && dp[v] == 0) {
                    cout << "-1\n";
                    return;
                }
            }
        }
    }

    cout << n - accumulate(dp.begin() + 1, dp.end(), 0) << endl;
    for(int i = 1; i <= n; ++i) {
        if(dp[i] == 0) {
            cout << p[i] << ' ';
        }
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}