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
 * Created: 2025/05/18 01:43:24
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

struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len, fail;
        std::array<int, ALPHABET> next;
        Node() : len(0), fail(0), next{} {}
    };
    
    std::vector<Node> t;
    
    AhoCorasick() {
        init();
    }
    
    void init() {
        t.assign(2, Node {});
        t[0].next.fill(1);
        t[0].len = -1;
    }
    
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    
    int add(const std::string &a) {
        int p = 1;
        for (auto c : a) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }
    
    void work() {
        std::queue<int> q;
        q.push(1);
        
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].fail].next[i];
                } else {
                    t[t[x].next[i]].fail = t[t[x].fail].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }
    
    int next(int p, int x) {
        return t[p].next[x];
    }
    
    int fail(int p) {
        return t[p].fail;
    }
    
    int len(int p) {
        return t[p].len;
    }
    
    int size() {
        return t.size();
    }
};

void solve() {
    while (true) {
        int n; cin >> n;
        if (n == 0) break;
        AhoCorasick ac;
        vector<pair<string, int>> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].first;
            a[i].second = ac.add(a[i].first);
        }
    
        ac.work();
    
        string s;
        cin >> s;
        int m = ac.size(), p = 1;
        vector<int> vis(m);
        for (auto x : s) {
            x -= 'a';
            p = ac.next(p, x);
            for (int u = p; u != 1; vis[u]++, u = ac.fail(u));
        }
    
        vector<int> ans(n + 1);
        for (int i = 1; i <= n; ++i) {
            ans[i] = vis[a[i].second];
        }
        int Max = *max_element(ans.begin() + 1, ans.end());
        cout << Max << endl;
        for (int i = 1; i <= n; ++i) {
            if (ans[i] == Max) {
                cout << a[i].first << endl;
            }
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