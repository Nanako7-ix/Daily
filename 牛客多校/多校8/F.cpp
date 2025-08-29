#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
template <class K, class V>
using hash_map = __gnu_pbds::gp_hash_table<K, V>;
/*
  -0
|1   |2
  -3
|4   |5
  -6
0 -> 0, 1, 2, 4, 5, 6
1 -> 2, 5
2 -> 0, 2, 3, 4, 6
3 -> 0, 2, 3, 5, 6
4 -> 1, 2, 3, 5
5 -> 0, 1, 3, 5, 6
6 -> 0, 1, 3, 4, 5, 6
7 -> 0, 2, 5
8 -> 0, 1, 2, 3, 4, 5, 6
9 -> 0, 1, 2, 3, 5, 6
*/

auto light = []() {
    const vector<vector<int>> L = {
        {0, 1, 2, 4, 5, 6},
        {2, 5},
        {0, 2, 3, 4, 6},
        {0, 2, 3, 5, 6},
        {1, 2, 3, 5},
        {0, 1, 3, 5, 6},
        {0, 1, 3, 4, 5, 6},
        {0, 2, 5},
        {0, 1, 2, 3, 4, 5, 6},
        {0, 1, 2, 3, 5, 6}
    };
    vector<int> res(1000);
    for (int i = 0; i < 1000; i++) {
        int x = i;
        for (int j = 0; j < 3; j++) {
            int d = x % 10;
            int Ld = 0;
            for (auto s : L[d]) Ld |= (1 << s);
            res[i] |= Ld << (7 * j);
            x /= 10;
        }
    }
    return res;
}();

auto states = []() {
    vector<int> res(1 << 21);
    for (int i = 0; i < (1 << 21); i++) {
        res[i] = i;
    }
    sort(res.begin(), res.end(), [](int x, int y) {
        return __builtin_popcount(x) < __builtin_popcount(y);
    });
    return res;
}();

int solve() {
    int MASK, n, m; cin >> MASK >> n >> m;
    cout << "dp[" << MASK << "] = ";
    vector<int> a(n);
    for (auto &i : a) cin >> i;
    for (auto &st : states) {
        bool isok = true;
        // set<int> occur;
        hash_map<int, int> occur;
        for (auto i : a) {
            if (occur[light[i] & st]) {
                isok = false;
                break;
            }
            occur[light[i] & st]++;
        }
        if (!isok) continue;
        return __builtin_popcount(st);
    }
    return 21;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cerr << t << "\r";
        cout << solve() << '\n';
    }
    return 0;
}
