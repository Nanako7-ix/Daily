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
struct TreapPool {
public:
	TreapPool()
private:
	static std::mt19937_64 rng;
	std::vector<T> val, sum;
	std::vector<int> ls, rs, fa, siz;
	std::vector<i64> phi;
};

template<typename T>
std::mt19937_64 TreapPool<T>::rng(chrono::steady_clock::now().time_since_epoch().count());

void Thephix() {
	int n;
	cin >> n;

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
