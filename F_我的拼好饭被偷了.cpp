// Author: Nanako7_ix
// Created: 2025/03/29 16:39:03
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

template<typename T>
struct Discrete {
    int ready;
    vector<T> a;

    Discrete() {
        init();
    }

    void init() {
        ready = 0, a.clear();
    }

    void insert(const T& v) {
        assert(!ready);
        a.push_back(v);
    }

    void work() {
        ready = 1;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int lower_bound(const T& v) {
        if(!ready) work();
        return ::lower_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    int upper_bound(const T& v) {
        if(!ready) work();
        return ::upper_bound(a.begin(), a.end(), v) - a.begin() + 1;
    }

    T operator[](int k) {
        if(!ready) work();
        return a[k - 1];
    }

    int size() {
        if(!ready) work();
        return a.size();
    }
};

void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> a(n + 1);
    Discrete<int> dis;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
        dis.insert(a[i][0]);
        dis.insert(a[i][1]);
    }
    for(int i = 1; i <= n; ++i) {
        a[i][0] = dis.lower_bound(a[i][0]);
        a[i][1] = dis.lower_bound(a[i][1]);
    }
    sort(a.begin() + 1, a.end(), [](array<int, 3> x, array<int, 3> y) {
        return x[0] > y[0];
    });

    vector<int> ans(n + 1);
    Fenwick<int> tr(dis.size());
    for(int i = 1; i <= n; ++i) {
        auto [l, r, id] = a[i];
        ans[id] = tr.query(1, r - 1);
        tr.modify(r, 1);
    }
    for(int i = 1; i <= n; ++i) {
        cout << ans[i] << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}