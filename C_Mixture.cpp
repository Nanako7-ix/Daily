#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

void Thephix() {
    int n;
    string s;
    cin >> n >> s;

    vector<int> vis(1 << n);
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (int i = 0; i < n; ++i) {
            if (u >> i & 1) continue;
            int v = u | (1 << i);
            if (s[v - 1] != '1' && !vis[v]) {
                q.push(v);
                vis[v] = 1;
            }
        }
    }

    if (vis[(1 << n) - 1]) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Thephix();
    }

    return 0;
}