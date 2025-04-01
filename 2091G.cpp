// Author: Nanako7_ix
// Created: 2025/03/26 11:37:01
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

int solve() {
    int n, k;
    cin >> n >> k;
    if(n % k == 0) return k;
    if(k * k <= n) return max(1, k - 2);
    vector<int> f(n + 1);
    f[0] = 1;
    for(int i = k; i > 1; --i) {
        vector<int> g(n + 1);
        if((k - i) & 1) {
            for(int j = n - i; j >= 0; --j) {
                g[j] = f[j + i] | g[j + i];
            }
        } else {
            for(int j = i; j <= n; ++j) {
                g[j] = f[j - i] | g[j - i];
            }
        }
        swap(f, g);
        if(f[n]) return i;
    }
    return 1;
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) cout << solve() << endl;
    return 0;
}