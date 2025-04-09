// Author: Nanako7_ix
// Created: 2025/04/08 22:38:06
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

constexpr int H = 30;

void solve() {
    int n, k;
    cin >> n >> k;
    
    int cnt = 1;
    vector<int> siz(31 * n), f(31 * n, inf), tag(31 * n);
    vector<array<int, 2>> ch(31 * n, array<int, 2> {});
    auto pull = [&](int u) -> void {
        siz[u] = siz[ch[u][0]] + siz[ch[u][1]];
        f[u] = min(f[ch[u][0]], f[ch[u][1]]);
    };
    auto push = [&](int u) -> void {
        if(tag[u] & 1) {
            swap(ch[u][0], ch[u][1]);
        }
        tag[ch[u][0]] ^= tag[u] >> 1;
        tag[ch[u][1]] ^= tag[u] >> 1;
        tag[u] = 0;
    };
    auto insert = [&](this auto&& insert, int u, int x, int bit, int info) {
        if(bit == -1) {
            siz[u]++, f[u] = min(f[u], info);
            return;
        }
        push(u);
        int b = x >> bit & 1;
        if(ch[u][b] == 0) {
            ch[u][b] = ++cnt;
        }
        insert(ch[u][b], x, bit - 1, info);
        pull(u);
    };
    auto modify = [&](int val) -> void {
        bitset<H> x;
        for(int i = 0; i < H; ++i) {
            x[H - i - 1] = val >> i & 1;
        }
        tag[1] ^= x.to_ullong();
    };
    auto find = [&](this auto&& find, int u, int bit, int sum) -> int {
        if(u == 0) return inf;
        if(bit == -1) {
            return f[u];
        }
        push(u);
        if(k >> bit & 1) {
            return find(ch[u][1], bit - 1, sum << 1 | 1);
        } else {
            return min(find(ch[u][0], bit - 1, sum << 1), f[ch[u][1]]);
        }
    };
    
    int ans = inf;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for(int i = n; i >= 1; --i) {
        insert(1, a[i], H - 1, i);
        modify(a[i]);
        ans = min(ans, find(1, H - 1, 0) - i + 1);
        modify(a[i]);
    }
    cout << (ans > n ? -1 : ans) << endl;
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