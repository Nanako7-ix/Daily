#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int Thephix = 0;
constexpr int N = 2000005;

struct Node {
    int leaf;
    int nxt[26];
} t[N];

i64 ans = 0;
int tot = 1;

void insert (string s) {
    int p = 1;
    for (int i = 0; i < (int) s.size(); ++i) {
        t[p].leaf++;
        if (t[p].nxt[s[i] - 'a'] == 0) {
            t[p].nxt[s[i] - 'a'] = ++tot;
        }
        p = t[p].nxt[s[i] - 'a'];
    }
    t[p].leaf++;
}

void dfs(int u) {
    if (u == 0) return;
    for (int i = 0; i < 26; ++i) {
        dfs(t[u].nxt[i]);
    }
    if (u != 1) {
        ans += 1LL * (t[u].leaf / 2) * ((t[u].leaf + 1) / 2);
    }
}

void solve () {
    int n;
    cin >> n;
    for (int i = 1; i <= n * 2; ++i) {
        string s;
        cin >> s;
        insert(s);
    }
    dfs(1);
    cout << ans << "\n";
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int T = 1;
    // cin >> T;
    while (T--) {
        solve ();
    }

    return Thephix;
}