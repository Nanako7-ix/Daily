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
 * Created: 2025/05/16 22:22:40
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

struct MaxAssignment {
    ll ans = 0, n;
    vector<int> fx, fy, pre, vx, vy;
    vector<ll> lx, ly, slack;
    MaxAssignment(graph g) : graph(g) {
        n = max(nx, ny);
        fx.resize(n + 1);
        fy.resize(n + 1);
        pre.resize(n + 1);
        vx.resize(n + 1);
        vy.resize(n + 1);
        lx.resize(n + 1);
        ly.resize(n + 1);
        slack.resize(n + 1);
        work();
    }
    void work() {
        for(int i = 1; i <= n; ++i) {
            lx[i] = *max_element(w[i].begin() + 1, w[i].end());
        }
        for(int i = 1; i <= n; ++i) {
            fill(vx.begin(), vx.end(), 0);
            fill(vy.begin(), vy.end(), 0);
            fill(slack.begin(), slack.end(), INF);
            bfs(i);
        }
        for(int i = 1; i <= n; ++i) {
            ans += lx[i] + ly[i];
        }
    }
    void bfs(int x) {
        queue<int> q;
        q.push(x);
        while(1) {
            while(!q.empty()) {
                int u = q.front();
                q.pop(), vx[u] = 1;
                for(int v = 1; v <= n; ++v) if(!vy[v]) {
                    ll tmp = lx[u] + ly[v] - w[u][v];
                    if(tmp <= slack[v]) {
                        slack[v] = tmp;
                        pre[v] = u;
                        if(!slack[v]) {
                            vy[v] = 1;
                            if(!fy[v]) {
                                for(int s = v; s; swap(s, fx[fy[s] = pre[s]]));
                                return;
                            } else q.push(fy[v]);
                        }
                    }
                }
            }

            ll d = INF;
            for(int i = 1; i <= n; ++i) if(!vy[i]) d = min(d, slack[i]);
            assert(d > 0);
            for(int i = 1; i <= n; ++i) {
                if(vx[i]) lx[i] -= d;
                if(vy[i]) ly[i] += d;
                else slack[i] -= d;
            }
            for(int v = 1; v <= n; ++v) {
                if(!vy[v] && !slack[v]) {
                    vy[v] = 1;
                    if(!fy[v]) {
                        for(int s = v; s; swap(s, fx[fy[s] = pre[s]]));
                        return;
                    } else q.push(fy[v]);
                }
            }
        }
    }
};

void solve() {
    
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