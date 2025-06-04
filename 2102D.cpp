/**
 * Author:  Nanako7_ix
 * Created: 2025/05/12 00:17:37
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

// void solve() {
//     int n;
//     cin >> n;
//     vector<int> a(n + 1), p(n + 1);
//     array<set<int>, 2> S {};
//     for (int i = 1; i <= n; ++i) {
//         cin >> a[i];
//         p[a[i]] = i;
//         S[i & 1].insert(a[i]);
//     }

//     auto Swap = [&](int i, int j) {
//         if (i == j) return;
//         int ti = i + 1, tj = j - i <= 4 ? i + 3 : j - 3;
//         swap(p[a[i]], p[a[j]]), swap(a[i], a[j]);
//         swap(p[a[ti]], p[a[tj]]), swap(a[ti], a[tj]);
//     };

//     for (int i = 1; i <= n - 3; ++i) {
//         int Min = *S[i & 1].begin();
//         Swap(i, p[Min]);
//         S[i & 1].erase(a[i]);
//     }

//     for (int i = 1; i <= n; ++i) {
//         cout << a[i] << " \n"[i == n];
//     }
// }

template<typename Info>
struct Fenwick {
private:
    int n;
    std::vector<Info> tr;
    constexpr int lowbit(int x) {
        return x & -x;
    }
public:
    Fenwick () = default;

    Fenwick (int n, Info e = {}) { init(n, e); }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    Fenwick (const Iterator& l, const Iterator& r) { init(l, r); }

    void init (int n, Info e = {}) {
        vector<Info> _(n, e);
        init(_.begin(), _.end());
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init (const Iterator& l, const Iterator& r) {
        n = r - l;
        tr.assign(n + 1, Info {});
        for(int i = 1; i <= n; ++i) {
            tr[i] += *(l + i - 1);
            if(i + lowbit(i) <= n) {
                tr[i + lowbit(i)] += tr[i];
            }
        }
    }

    void modify (int p, const Info& v) {
        for(; p <= n; p += lowbit(p)) {
            tr[p] += v;
        }
    }

    Info query (int p) {
        Info res{};
        for(; p; p -= lowbit(p)) {
            res += tr[p];
        }
        return res;
    }

    Info query (int l, int r) {
        assert(l <= r && l != 0);
        return query(r) - query(l - 1);
    }

    int lower_bound (Info k) {
        int x = 0;
        for(int i = 1 << std::__lg(n); i; i >>= 1)
            if(x + i <= n && tr[x + i] < k)
                k -= tr[x += i];
        return x + 1;
    }

    int upper_bound (Info k) {
        int x = 0;
        for(int i = 1 << std::__lg(n); i; i >>= 1)
            if(x + i <= n && tr[x + i] <= k)
                k -= tr[x += i];
        return x + 1;
    }
};

int inv(vector<int> a) {
    int ans = 0, m = *ranges::max_element(a);
    Fenwick<i64> tr(m);
    for (auto x : a) {
        ans ^= tr.query(x, m) & 1;
        tr.modify(x, 1);
    }
    return ans & 1;
}

void solve () {
    int n;
    cin >> n;
    array<vector<int>, 2> a;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a[i & 1].push_back(x);
    }
    int p = inv(a[0]) ^ inv(a[1]);
    ranges::sort(a[0]), ranges::sort(a[1]);
    if (p) swap(a[(n - 1) & 1][a[(n - 1) & 1].size() - 1], a[(n - 1) & 1][a[(n - 1) & 1].size() - 2]);
    for (int i = 0; i < n; ++i) {
        cout << a[i & 1][i >> 1] << ' ';
    }
    cout << endl;
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