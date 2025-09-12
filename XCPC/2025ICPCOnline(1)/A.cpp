#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

struct status {
	int panelty;
	bool ac;
	status() : panelty(0), ac(false) {}
};

void Thephix() {
	int n;
	cin >> n;
	vector<tuple<string, int, int, string>> submitsions(n);
	for (int i = 0; i < n; ++i) {
		char problem;
		auto& [name, id, t, verdict] = submitsions[i];
		cin >> name >> problem >> t >> verdict;
		id = problem - 'A';
	}
	sort(submitsions.begin(), submitsions.end(),
		[](const auto& x, const auto& y) {
			return get<2>(x) < get<2>(y);
		}
	);

	map<string, array<status, 26>> best, worst;
	for (int i = 0; i < n; ++i) {
		auto& [name, id, t, verdict] = submitsions[i];
		if (!best[name][id].ac) {
			if (verdict == "Accepted" || verdict == "Unknown") {
				best[name][id].ac = 1;
				best[name][id].panelty += t;
			} else {
				best[name][id].panelty += 20;
			}
		}
		if (!worst[name][id].ac) {
			if (verdict == "Accepted") {
				worst[name][id].ac = 1;
				worst[name][id].panelty += t;
			} else {
				worst[name][id].panelty += 20;
			}
		}
	}

	vector<tuple<string, int, int>> teams;
	for (auto [name, dp] : worst) {
		int ac = 0, penalty = 0;
		for (int i = 0; i < 26; ++i) {
			if (dp[i].ac) {
				ac++, penalty += dp[i].panelty;
			}
		}
		teams.emplace_back(name, ac, penalty);
	}

	sort(teams.begin(), teams.end(), [](const auto& x, const auto& y) {
		if (get<1>(x) != get<1>(y)) {
			return get<1>(x) > get<1>(y);
		} return get<2>(x) < get<2>(y);
	});

	for (auto [name, dp] : best) {
		int ac = 0, penalty = 0;
		for (int i = 0; i < 26; ++i) {
			if (dp[i].ac) {
				ac++, penalty += dp[i].panelty;
			}
		}

		int ok = 1;
		for (int i = 0; i < (int) teams.size(); ++i) {
			auto& [_name, _ac, _penalty] = teams[i];
			if (_name == name) continue;
			if (ac < _ac || (ac == _ac && penalty > _penalty)) {
				ok = 0;
			}
			break;
		}

		if (ok) cout << name << " ";
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
