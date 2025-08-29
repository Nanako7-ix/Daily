#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

auto getFail (const std::string& s) {
	int n = s.size();
	std::vector<int> fail(n + 1);
	for (int i = 1, j = 0; i < n; ++i) {
		while (j && s[i] != s[j]) j = fail[j];
		fail[i + 1] = j += (s[i] == s[j]);
	}
	return fail;
}

void Thephix() {
	string s;
	cin >> s;
	auto fail = getFail(s);

	set<int> S(fail.begin() + 1, fail.end() - 1);
	
	int n = s.size();
	int border = fail[n];
	while (true) {
		
	}
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