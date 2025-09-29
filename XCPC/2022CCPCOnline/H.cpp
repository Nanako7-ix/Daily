#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

template<typename T>
bool is_prime(const T& x) {
	if (x == 2 || x == 3 || x == 5 || x == 7) return true;
	if (x < 2 || x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
	if (x < 121) return x > 1;
	const T d = (x - 1) >> __builtin_ctzll(x - 1);
	auto isok = [&](T a) -> bool {
		T y = 1, t = d;
		for (T i = a, j = d; j; j >>= 1) {
			if (j & 1) y = (i128) y * i % x;
			i = (i128) i * i % x;
		}
		while (y != 1 && y != x - 1 && t != x - 1) {
			y = (i128) y * y % x;
			t <<= 1;
		}
		return y == x - 1 || t % 2 == 1;
	};

	if (x < (1LL << 32)) for (T a : { 2, 7, 61 }) {
		if (!isok(a)) return false;
	} else for (T a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
		if (!isok(a)) return false;
	}
	return true;
}

std::mt19937_64 rng_64((std::random_device())());
auto rng(i64 L, i64 R) { return rng_64() % (R - L + 1) + L; }

template<typename T>
T pollard_rho(T n) {
	if (n <= 1) return n;
	const T c = rng(1, n - 1);
	auto f = [&](T x) { return ((i128) x * x % n + c) % n; };
	T x = 1, y = 2, z = 1, q = 1, g = 1;
	const T m = 1LL << (__lg(n) / 5);
	for (T r = 1; g == 1; r <<= 1) {
		x = y;
		for (T i = 0; i < r; ++i) y = f(y);
		for (T k = 0; k < r && g == 1; k += m) {
			z = y;
			for (T i = 0; i < min(m, r - k); ++i) {
				y = f(y);
				q = (i128) q * abs(x - y) % n;
			}
			g = gcd(q, n);
		}
	}
	if (g == n) do {
		z = f(z);
		g = gcd(abs(x - z), n);
	} while (g == 1);
	return g;
}

template<typename T>
T find_prime_factor(T n) {
	if (is_prime(n)) return n;
	for (int i = 0; i < 100; ++i) {
		T p = pollard_rho(n);
		if (is_prime(p)) return p;
		n = p;
	}
	return -1;
}

template<typename T>
auto factor(T n) {
	std::vector<std::pair<T, int>> res;
	for (int p = 2; p * p <= n && p < 100; ++p) {
		if (n % p) continue;
		int e = 0;
		do { n /= p, e++; } while (n % p == 0);
		res.emplace_back(p, e);
	}
	while (n > 1) {
		T p = find_prime_factor(n);
		int e = 0;
		do { n /= p, e++; } while (n % p == 0);
		res.emplace_back(p, e);
	}
	return res;
}

template<typename T, bool SORT = true>
std::vector<T> divisor(std::vector<std::pair<T, int>> pf) {
	std::vector<T> res = { 1 };
	for (auto& [p, e] : pf) {
		int siz = res.size();
		for (int i = 0; i < siz; ++i) {
			T x = 1;
			for (int j = 0; j < e; ++j) {
				x *= p;
				res.push_back(res[i] * x);
			}
		}
	}
	if (SORT) std::sort(res.begin(), res.end());
	return res;
}

constexpr array<i64, 60> p = []() {
	array<i64, 60> p {};
	p[0] = 1;
	for (int i = 1; i < 60; ++i) {
		p[i] = p[i - 1] * 2;
	}
	return p;
} ();

void Thephix() {
	i64 l, r, k;
	cin >> l >> r >> k;

	vector<i64> ans;
	for (i64 x : divisor<i64, false>(factor(k))) {
		i64 k1 = (l + x - 1) / x;
		i64 k2 = r / x;
		if (k1 > k2) continue;
		if (k2 - k1 >= 60) continue;
		i128 res = i128(x) * (k1 + k2) * (k2 - k1 + 1) / 2 * p[k2 - k1];
		if (res == k) ans.push_back(x);
	}

	if (ans.size() > 100000) {
		cout << "Too Many!\n";
		return;
	}

	if (ans.empty()) {
		cout << "No Solution\n";
		return;
	}

	sort(ans.begin(), ans.end());
	cout << ans.size() << "\n";
	for (i64 x : ans) {
		cout << x << " ";
	}
	cout << "\n";
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
