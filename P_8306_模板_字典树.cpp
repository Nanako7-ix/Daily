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
 * Created: 2025/05/15 22:49:04
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

template<int N>
struct Trie {
    int cnt = 0;
    vector<int> f;
    vector<array<int, N>> nxt;
    static int rank(char);

    Trie(int n = 2e6) {
        f.reserve(n), f.assign(1, 0);
        nxt.reserve(n), nxt.assign(1, {});
    }

    int Node() {
        f.push_back(0);
        nxt.push_back({});
        return ++cnt;
    }

    void insert(const string& s) {
        int n = s.size(), p = 0;
        for(int i = 0; i < n; ++i) {
            int x = rank(s[i]);
            if(!nxt[p][x]) {
                nxt[p][x] = Node();
            }
            f[p]++;
            p = nxt[p][x];
        }
        f[p]++;
    }

    int query(const string& s) {
        int n = s.size(), p = 0;
        for(int i = 0; i < n; ++i) {
            int x = rank(s[i]);
            if(!nxt[p][x]) return 0;
            p = nxt[p][x];
        }
        return f[p];
    }
};

template<>
int Trie<62>::rank(char x) {
    if ('a' <= x && x <= 'z') {
        return x - 'a';
    }
    if ('A' <= x && x <= 'Z') {
        return x - 'A' + 26;
    }
    return x - '0' + 52;
}

void solve() {
    int n, q;
    cin >> n >> q;
    Trie<62> tr;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        tr.insert(s);
    }
    for (int i = 1; i <= q; ++i) {
        string s;
        cin >> s;
        cout << tr.query(s) << endl;
    }
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