#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

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

i64 inv(vector<int>& a) {
    i64 ans = 0;
    int n = a.size() - 1, m = *max_element(a.begin() + 1, a.end());
    Fenwick<int> tr(m);
    for (int i = n; i >= 1; --i) {
        ans += tr.query(a[i]);
        tr.modify(a[i], 1);
    }
    return ans;
}

void Thephix() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    i64 ans = inv(a);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            for (int k = i; k <= j; ++k) {
                a[k] = 2 * n - a[k];
            }
            ans = min(ans, inv(a));
            for (int k = i; k <= j; ++k) {
                a[k] = 2 * n - a[k];
            }
        }
    }
    cout << ans << "\n";
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