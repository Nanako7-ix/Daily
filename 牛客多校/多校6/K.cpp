#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T, typename Func>
class SparseTable {
private:
    int n;
    Func op;
    std::vector<std::vector<T>> st;
public:
    SparseTable () = default;

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SparseTable (const Iterator& l, const Iterator& r, Func&& f) : op(f) {
        init(l, r);
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init (const Iterator& l, const Iterator& r) {
        n = r - l;
        st.assign(std::__lg(n) + 1, std::vector<T> (n + 1));
        for (int i = 1; i <= n; ++i) {
            st[0][i] = *(l + i - 1);
        }
        for (int i = 1; i <= std::__lg(n); ++i) {
            for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
                st[i][j] = op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T operator () (int l, int r) {
        assert(l <= r);
        int k = std::__lg(r - l + 1);
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }

    T query (int l, int r) {
        T res {};  
        int len = r - l + 1;
        for (int i = 0, k = l; i <= std::__lg(len); ++i) {
            if(len >> i & 1) {
                res = k == l ? st[i][l] : op(res, st[i][k]);
                k += 1 << i;
            }
        }
        return res;
    }
};

template<typename Iterator, typename Func>
SparseTable (const Iterator&, const Iterator&, Func&&) ->
SparseTable<typename std::iterator_traits<Iterator>::value_type, Func>;

void Thephix() {
    int n, single = 1;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        single &= a[i] == a[1];
    }

    if (single) {
        cout << "0\n";
        return;
    }

    vector<int> dis(n + 1);
    for (int i = 2; i <= n; ++i) {
        dis[i] = a[i] - a[i - 1];
    }

    SparseTable Gcd(dis.begin() + 1, dis.end(), [](int x, int y) {
        return std::gcd(x, y);
    });

    vector<int> pre(n + 1), suf(n + 2);
    for (int i = 1; i <= n; ++i) {
        pre[i] = std::gcd(pre[i - 1], a[i]);
    }
    for (int i = n; i >= 1; --i) {
        suf[i] = std::gcd(suf[i + 1], a[i]);
    }
    
    vector<int> L {n}, R {1};
    while (L.back() != 0) {
        int p = L.back();
        int l = 0, r = p - 1, res = -1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (pre[m] != pre[p]) {
                res = m, l = m + 1;
            } else r = m - 1;
        }
        assert(res != -1);
        L.push_back(res);
    }

    while (R.back() != n + 1) {
        int p = R.back();
        int l = p + 1, r = n + 1, res = -1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (suf[m] != suf[p]) {
                res = m, r = m - 1;
            } else l = m + 1;
        }
        assert(res != -1);
        R.push_back(res);
    }

    int ans = 0;
    for (auto l : L) {
        for (auto r : R) {
            if (l >= r) continue;
            int res = std::gcd(pre[l], suf[r]);
            if (l + 2 <= r - 1) {
                res = std::gcd(res, Gcd(l + 2, r - 1));
            }
            ans = max(ans, res);
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