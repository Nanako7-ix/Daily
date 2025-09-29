#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

// 停一次，走四步：消耗九滴血，五次行动，走四步
// 停一次，走三步：消耗五滴血，四次行动，走三步
// 停一次，走两次：消耗两滴血，三次行动，走两步
// 停一次，走一次：不消耗血量，两次行动，走一步
// 发现最终只会执行两种策略！
// [  x * f(i)  , x * (i + 1), x * i]
// [y * f(i + 1), y * (i + 2), y * (i + 1)]

i64 exgcd(u64 a, u64 b, i64& x, i64& y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	i64 d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

i64 f(i64 i) {
	return (i * i + i) / 2 - 1;
}

i64 g(i64 d, i64 i) {

}

void Thephix() {
	int n, d;
	cin >> n >> d;
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
