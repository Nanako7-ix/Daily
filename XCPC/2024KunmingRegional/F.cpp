#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

template<typename T>
struct Min_25 {
	Min_25(i64 n) { init(n); }	

	i64 n, sq, m;
	vector<T> g1, g2;

	T& g(i64 k) { return k <= sq ? g1[k] : g2[n / k]; }
	T f(i64) { return 1; }
	T sum(i64 x) { return x; }
	
	void init(i64 n) {
		this -> n = n;
		this -> sq = [n]() {
			i64 t = std::sqrt(n);
			while (t * t > n) --t;
			while ((t + 1) * (t + 1) < n) ++t;
			return t;
		} ();
		
		g1.assign(sq + 1, T());
		g2.assign(sq + 1, T());

		sieve(sq);
		m = P.size();
		vector<T> pre(m + 1);
		for (int i = 0; i < m; ++i) {
			pre[i + 1] = pre[i] + f(P[i]);
		}

		vector<i64> x;
		for (i64 k = 1; k <= n; ++k) {
			g(n / k) = sum(n / k) - f(1);
			x.push_back(n / k);
			k = n / (n / k);
		}
		
		for (i64 j = 0; j < m; ++j) {
			i64 p = P[j];
			for (i64 x : x) {
				if (p * p > x) break;
				g(x) -= f(p) * (g(x / p) - pre[j]);
			}
		}
	}

	std::vector<i64> minp, P;

	void sieve(i64 n) {
		minp.assign(n + 1, 0);
		P.clear();
		for (i64 i = 2; i <= n; ++i) {
			if (minp[i] == 0) {
				P.push_back(minp[i] = i);
			}
			for (i64& p : P) {
				if(i * p > n) break;
				minp[i * p] = p;
				if(i % p == 0) break;
			}
		}
	}
};

i64 power(i64 a, i64 b, i64 Mod) {
	i64 res = 1;
	for (a %= Mod; b; b >>= 1, a = a * a % Mod) {
		if (b & 1) res = res * a % Mod;
	}
	return res;
}

void Thephix() {
	i64 n, Mod;
	cin >> n >> Mod;

	Min_25<i64> min_25(n);
	auto& P = min_25.P;
	int m = P.size();

	auto dfs = [&](this auto&& dfs, i64 n, int x, int cnt) -> i64 {
		if (cnt == 1) {
			i64 res = min_25.g(n) - x;
			for (int i = x; i < m && P[i] * P[i] <= n; ++i) {
				for (i64 j = P[i] * P[i]; j <= n; j *= P[i]) {
					res++;
				}
			}
			return res;
		}
		i64 res = 0;
		for (int i = x; i < m && P[i] * P[i] <= n; ++i) {
			for (i64 j = P[i]; j * P[i] <= n; j *= P[i]) {
				res += dfs(n / j, i + 1, cnt - 1);
			}
		}
		return res;
	};

	i64 ans = 1;
	for (int w = 2; w <= 10; ++w) {
		i64 cnt = dfs(n, 0, w);
		ans = ans * power(w, cnt, Mod) % Mod;
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
