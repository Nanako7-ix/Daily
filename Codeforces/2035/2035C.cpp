// Author: Nanako7_ix
// Created: 2025/03/31 20:56:33
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

vector<int> f(int n) {
    assert(n >= 6 && n % 2 == 0);

    vector<int> a(n + 1), vis(n + 1);
    for(int i = n - (__lg(n) << 1) + 1, j = 2; i <= n; i += 2, j <<= 1) {
        vis[a[i + 1] = j] = 1;
        vis[a[i] = j - 1] = 1;
    }

    vis[a[n - (__lg(n) << 1)] = 5] = 1;
    for(int i = 1, j = 1; i <= n; ++i, ++j) {
        if(a[i]) break;
        while(vis[j]) ++j;
        a[i] = j;
    }
    return a;
}

void solve() {
    int n;
    cin >> n;

    if(n == 5) {
        cout << "5\n2 1 3 4 5\n";
        return;
    }

    auto a = f(n ^ (n & 1));
    if(n & 1) {
        cout << n << endl;
        a.push_back(n);
    } else {
        cout << (1 << (__lg(n) + 1)) - 1 << endl;
    }

    for(int i = 1; i <= n; ++i) {
        cout << a[i] << " \n"[i == n];
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}