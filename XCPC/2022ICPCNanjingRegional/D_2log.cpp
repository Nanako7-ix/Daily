#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

using namespace __gnu_pbds;

template<typename T,
template<typename Node_CItr, typename Node_Itr, typename Cmp_Fn_, typename _Alloc_>
typename update = tree_order_statistics_node_update>
struct Tree : tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update> {
using super = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, update>;
	int tot = 0;
	void insert(const T& v) { super::insert({v, ++tot}); }
	void erase(const T& v) { super::erase(super::lower_bound({v, 0})); }
	T find_by_order(int k) { return super::find_by_order(k - 1) -> first; }
	int order_of_key(const T& v) { return super::order_of_key({v, 0}) + 1; }
	T prev(const T& v) { return find_by_order(order_of_key(v) - 1); }
	const T next(const T& v) { return find_by_order(order_of_key(v + 1)); }
};

constexpr i64 inf = 1E15;

void Thephix() {
	int n, k, m;
	i64 a1, d;
	cin >> n >> k >> m >> a1 >> d;

	vector<i64> a(n + 1), f(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		f[i] = a[i] + a1 + i * d;
	}

	Tree<i64> in, out;
	for (int i = 1; i < m; ++i) {
		in.insert(f[i]);
	}
	for (int i = m; i <= n; ++i) {
		out.insert(a[i]);
	}
	
	i64 ans = 0;
	for (int l = 1, r = m; r <= n; ++l, ++r) {
		out.erase(a[r]);
		in.insert(f[r]);
		
		auto check = [&](i64 x) -> bool {
			int cnt = 0;
			cnt += out.size() - (out.order_of_key(x + 1) - 1);
			cnt += in.size() - (in.order_of_key(x + l * d + 1) - 1);
			return cnt < k;
		};
		
		i64 x = 0, y = inf, res = -1;
		while (x <= y) {
			i64 mid = (x + y) >> 1;
			if (check(mid)) {
				res = mid, y = mid - 1;
			} else x = mid + 1;
		}

		assert(res != -1);
		ans = max(ans, res);
		
		out.insert(a[l]);
		in.erase(f[l]);
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
