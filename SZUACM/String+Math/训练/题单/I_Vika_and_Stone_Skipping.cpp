/**
 *
 *  $$$$$$\  $$$$$$\  $$$$$$\  $$\       $$\       $$$$$$\  
 * $$  __$$\ \_$$  _|$$  __$$\ $$ |      $$ |     $$  __$$\ 
 * $$ /  \__|  $$ |  $$ /  $$ |$$ |      $$ |     $$ /  $$ |
 * $$ |        $$ |  $$$$$$$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |        $$ |  $$  __$$ |$$ |      $$ |     $$ |  $$ |
 * $$ |  $$\   $$ |  $$ |  $$ |$$ |      $$ |     $$ |  $$ |
 *  $$$$$$ | $$$$$$\ $$ |  $$ |$$$$$$$$\ $$$$$$$$\ $$$$$$  |
 * \______/  \______|\__|  \__|\________|\________|\______/ 
 *
 * Author:  Nanako7_ix
 * Created: 2025/05/22 15:05:00
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

vector<int> minp, primes;
void sieve(int N) {
    minp.assign(N + 1, 0);
    primes.clear();
    for(int i = 2; i <= N; ++i) {
        if(!minp[i]) primes.emplace_back(minp[i] = i);
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

constexpr i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if(b == 0) {
        assert(a != 0);
        x = a / std::abs(a), y = 0;
        return std::abs(a);
    }
    i64 d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

struct Barrett {
public:
    Barrett(u32 _m) : m(_m), im((u64)(-1) / _m + 1) {}
    constexpr u32 Mod() const { return m; }
    constexpr u32 mul(u32 a, u32 b) const {
        u64 z = 1LL * a * b;
        u64 x = u64((u128(z) * im) >> 64);
        u32 v = u32(z - x * m);
        if (m <= v) v += m;
        return v;
    }
private:
    u32 m;
    u64 im;
};

template<u32 Id>
struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}

    template<std::unsigned_integral T>
    constexpr DynModInt(T v) : x(v % Mod()) {}

    template<std::signed_integral T>
    constexpr DynModInt(T v) {
        int t = v % int(Mod());
        if(t < 0) {
            t += Mod();
        }
        x = t;
    }

    constexpr static void setMod(u32 m) {
        bt = m;
    }

    constexpr static u32 Mod() {
        return bt.Mod();
    }

    constexpr u32 val() const {
        return x;
    }

    constexpr DynModInt operator-() const {
        return x == 0 ? 0 : Mod() - x;
    }

    constexpr DynModInt inv() const {
        i64 x, y;
        assert(exgcd(this -> x, Mod(), x, y) == 1);
        return x;
    }

    constexpr DynModInt& operator+=(const DynModInt& rhs) & {
        x += rhs.val();
        if(x >= Mod()) {
            x -= Mod();
        }
        return *this;
    }

    constexpr DynModInt& operator-=(const DynModInt& rhs) & {
        x -= rhs.val();
        if(x >= Mod()) {
            x += Mod();
        }
        return *this;
    }

    constexpr DynModInt& operator*=(const DynModInt& rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }

    constexpr DynModInt& operator/=(const DynModInt& rhs) & {
        return *this *= rhs.inv();
    }

    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt& rhs) {
        return lhs += rhs;
    }

    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt& rhs) {
        return lhs -= rhs;
    }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt& rhs) {
        return lhs *= rhs;
    }

    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt& rhs) {
        return lhs /= rhs;
    }

    friend constexpr std::strong_ordering operator<=> (const DynModInt &lhs, const DynModInt &rhs) = default;

    friend std::istream& operator>>(std::istream& is, DynModInt& a) {
        i64 x;
        is >> x;
        a = DynModInt {x};
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const DynModInt& a) { 
        os << a.val();
        return os;
    }
private:
    u32 x;
    static Barrett bt;
};

template<u32 Id> Barrett DynModInt<Id>::bt = 998244353;

using m32 = DynModInt<0>;

#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)
template<typename Info>
struct SegmentTree {
    constexpr static int inf = 0x3f3f3f3f;
    using i64 = long long;
    int n;
    std::vector<Info> info;

    SegmentTree() = default;

    SegmentTree(int n, Info e = {}) { init(n, e); }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    SegmentTree(const Iterator& l, const Iterator& r) { init(l, r); }

    void init(int n, Info e = {}) {
        vector<Info> _(n, e);
        init(_.begin(), _.end());
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void init(const Iterator& l, const Iterator& r) {
        n = r - l;
        info.assign(4 << std::__lg(n), Info {});
        build(1, 1, n, l);
    }

    void pull(int u) {
        info[u] = info[ls(u)] + info[rs(u)];
    }

    template<typename Iterator, typename = std::_RequireInputIter<Iterator>>
    void build(int u, int l, int r, const Iterator& it) {
        if (l == r) {
            info[u] = {*it};
            return;
        }
        int m = (l + r) >> 1;
        build(ls(u), l, m, it);
        build(rs(u), m + 1, r, it + (m - l + 1));
        pull(u);
    }

    template<typename Func>
    void modify(int p, Func&& op, int u, int l, int r) {
        if (l == r) {
            op(info[u]);
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m) {
            modify(p, op, ls(u), l, m);
        } else {
            modify(p, op, rs(u), m + 1, r);
        }
        pull(u);
    }

    template<typename Func>
    void modify(int p, Func&& op) {
        modify(p, op, 1, 1, n);
    }

    Info query(int L, int R, int u, int l, int r) {
        if (L <= l && r <= R) {
            return info[u];
        }
        int m = (l + r) >> 1;
        if (R <= m) {
            return query(L, R, ls(u), l, m);
        } else if (L > m) {
            return query(L, R, rs(u), m + 1, r);
        } else {
            return query(L, R, ls(u), l, m) + query(L, R, rs(u), m + 1, r);
        }
    }

    Info query(int l, int r) {
        assert(l <= r);
        return query(l, r, 1, 1, n);
    }

    int kth(i64 k, int u, int l, int r) {
        assert(info[u].size() >= k);
        if(l == r) return l;
        int m = (l + r) >> 1;
        if(info[ls(u)].size() >= k) {
            return kth(k, ls(u), l, m);
        } else {
            return kth(k - info[ls(u)].size(), rs(u), m + 1, r);
        }
    }

    int kth(i64 k) {
        assert(info[1].size() >= k);
        return kth(k, 1, 1, n);
    }

    template<typename Func>
    int FindFirst(int L, int R, Func&& f, int u, int l, int r) {
        if(l > R || r < L || !f(info[u])) return inf;
        if(l == r) return l;
        int m = (l + r) >> 1;
        int res = FindFirst(L, R, f, ls(u), l, m);
        if(res == inf) {
            res = FindFirst(L, R, f, rs(u), m + 1, r);
        }
        return res;
    }

    template<typename Func>
    int FindFirst(int l, int r, Func&& f) {
        assert(l <= r);
        return FindFirst(l, r, f, 1, 1, n);
    }

    template<typename Func>
    int FindLast(int L, int R, Func&& f, int u, int l, int r) {
        if(l > R || r < L || !f(info[u])) return -inf;
        if(l == r) return l;
        int m = (l + r) >> 1;
        int res = FindLast(L, R, f, rs(u), m + 1, r);
        if(res == -inf) {
            res = FindLast(L, R, f, ls(u), l, m);
        }
        return res;
    }

    template<typename Func>
    int FindLast(int l, int r, Func&& f) {
        assert(l <= r);
        return FindLast(l, r, f, 1, 1, n);
    }
};
#undef ls
#undef rs

struct Info {
    m32 val;
    Info (m32 x = 1) { val = x; }
};

Info operator+ (const Info& x, const Info& y) {
    return Info { x.val * y.val };
}

void solve() {
    sieve(1E6);
    int n, q, mod;
    cin >> n >> q >> mod;
    m32::setMod(mod);

    while (n % 2 == 0) {
        n /= 2;
    }

    int m = primes.size();
    SegmentTree<Info> seg(m);
    for (int i = 0; n != 1 && i < m; ++i) {
        int cnt = 0;
        while (n % primes[i] == 0) {
            n /= primes[i];
            cnt++;
        }
        if (i != 0) {
            seg.modify(i + 1, [&](Info& d) {
                d = Info {cnt + 1};
            });
        }
    }

    m32 ans = n == 1 ? 1 : 2;
    for (int i = 1; i <= q; ++i) {
        int x; cin >> x;
        while (x != 1) {
            int id = lower_bound(primes.begin(), primes.end(), minp[x]) - primes.begin();
            int cnt = 0;
            while (x % primes[id] == 0) {
                x /= primes[id];
                cnt++;
            }
            if (id != 0) {
                seg.modify(id + 1, [&](Info& d) {
                    d.val += cnt;
                });
            }
        }
        cout << ans * seg.query(1, m).val << endl;
    }
}

signed main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}