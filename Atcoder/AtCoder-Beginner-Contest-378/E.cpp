#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

template<typename T>
struct BIT {
	int n;
	std::vector<T> tr;
	constexpr int lowbit(int x) { return x & -x; }

	BIT () = default;

	BIT (int n, const T& e = T()) { init(n, e); }

	template<typename Func>
	BIT (int n, Func&& f) { init(n, f); }

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	BIT (const Iter& l, const Iter& r) { init(l, r); }

	void init (int n, const T& e = T()) {
		init(n, [&](int) { return e; });
	}

	template<typename Iter, typename = std::_RequireInputIter<Iter>>
	void init (const Iter& l, const Iter& r) {
		init(r - l, [&](int p) { return l[p - 1]; });
	}

	template<typename Func>
	void init (int n, Func&& f) {
		this -> n = n;
		tr.assign(n + 1, T {});
		for(int i = 1; i <= n; ++i) {
			tr[i] += f(i);
			if(i + lowbit(i) <= n) {
				tr[i + lowbit(i)] += tr[i];
			}
		}
	}

	void modify (int p, const T& v) {
		for(; p <= n; p += lowbit(p)) {
			tr[p] += v;
		}
	}

	T query (int p) {
		T res {};
		for(; p; p -= lowbit(p)) {
			res += tr[p];
		}
		return res;
	}

	T query (int l, int r) {
		return query(r) - query(l - 1);
	}

	int lower_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] < k) {
				k -= tr[x += i];
			}
		}
		return x + 1;
	}

	int upper_bound (T k) {
		int x = 0;
		for(int i = 1 << std::__lg(n); i; i >>= 1) {
			if(x + i <= n && tr[x + i] <= k) {
				k -= tr[x += i];
			}
		}
		return x + 1;
	}
};

void Thephix() {
	int n, m;
	cin >> n >> m;
	BIT<i64> f(2 * m);

	i64 s = 0, ans = 0;
	for (int i = 1; i <= n; ++i) {
		f.modify(s + 1, s);
		f.modify(s + m + 1, s + m);
		int x; cin >> x;
		s = ((s - x) % m + m) % m;
		ans += f.query(s + 1, s + m) - s * i;
	}
	cout << ans << "\n";
}

int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int T = 1;
	// cin >> T;

	while (T--) {
		Thephix();
	}

	return 0;
}
