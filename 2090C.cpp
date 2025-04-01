// Author: Nanako7_ix
// Created: 2025/03/24 22:41:48
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define setpre(x) fixed << setprecision(x)
#define debug(x) cerr << #x << " = " << x << "\n"
// #define endl "\n"
using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n;
    cin >> n;

    map<array<int, 2>, int> vis;
    queue<array<int, 2>> q0, q1;
    int t0 = 2, t1 = 2;
    q0.push({1, 1}), q1.push({1, 1});
    auto add0 = [&]() {
        t0++;
        for(int i = 1; i < t0; ++i) {
            if(i % 3 == 0 && (t0 - i) % 3 == 0) {
                q0.push({i - 1, t0 - i - 1});
            }
            if(i % 3 == 0 || (t0 - i) % 3 == 0) {
                continue;
            }
            if(i % 3 == 2 && (t0 - i) % 3 == 2) {
                continue;
            }
            q0.push({i, t0 - i});
        }
    };
    auto add1 = [&]() {
        t1++;
        if(t1 % 3 != 2) return;
        for(int i = 1; i < t1; ++i) {
            if(i % 3 == 0 && (t1 - i) % 3 == 0) {
                q1.push({i - 1, t0 - i - 1});
            }
            if(i % 3 == 0 || (t1 - i) % 3 == 0) {
                continue;
            }
            if(i % 3 == 2 && (t1 - i) % 3 == 2) {
                continue;
            }
            q1.push({i, t1 - i});
        }
    };
    auto find0 = [&]() {
        while(1) {
            while(q0.empty()) add0();
            auto [x, y] = q0.front();
            q0.pop();
            if(x % 3 == 1 && y % 3 == 1 && vis[{x / 3, y / 3}]) {
                continue;
            }
            return array<int, 2> {x, y};
        }
    };
    auto find1 = [&]() {
        while(1) {
            while(q1.empty()) add1();
            auto [x, y] = q1.front();
            q1.pop();
            if(vis[{x / 3, y / 3}]) {
                continue;
            }
            return array<int, 2> {x, y};
        }
    };

    for(int i = 1; i <= n; ++i) {
        int t; cin >> t;
        // cout << t << endl;
        if(t == 1) {
            auto [x, y] = find0();
            vis[{x / 3, y / 3}] = 1;
            cout << x << " " << y << endl;
        } else {
            auto [x, y] = find1();
            vis[{x / 3, y / 3}] = 1;
            cout << x << ' ' << y << endl;
        }
    }
    // add0(), add0(), add0(), add0();
    // while(q0.size()) {
    //     auto [x, y] = q0.front();
    //     cout << x << " " << y << endl;
    //     q0.pop();
    // }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
    return 0;
}