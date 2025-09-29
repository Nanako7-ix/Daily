#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1000005;
int fa[N];

int find(int u) {
    if (fa[u] == u) return u;
    return fa[u] = find(fa[u]);
}

int merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return 0;
    fa[x] = y;
    return 1;
}

int main () {
    cin.tie(nullptr), cout.tie(nullptr) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    int cnt = n, ans = 0;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        if (merge(u, v)) {
            cnt--;
        } else {
            ans++;
        }
    }
    ans += cnt - 1;
    cout << ans << "\n";
}