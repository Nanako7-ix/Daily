#include <bits/stdc++.h>
using namespace std;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using f64  = double;
using f128 = __float128;

#include <bits/stdc++.h>

struct AhoCorasick {
  static constexpr int N = 26;
  struct Node {
    int len, fail;
    std::vector<int> adj;
    std::array<int, N> next;
    Node() : len(0), fail(0), adj{}, next{} {}
  };

  std::vector<Node> t;
  
  AhoCorasick(int n = 0) {
    t.reserve(n);
    t.assign(2, Node());
    t[0].next.fill(1);
    t[0].len = -1;
    t[0].adj.push_back(1);
  }
  
  int newNode() {
    t.emplace_back();
    return t.size() - 1;
  }
  
  int insert(const std::string& s) {
    int p = 1;
    for (auto c : s) {
      int x = c - 'a';
      if (t[p].next[x] == 0) {
        t[p].next[x] = newNode();
        t[t[p].next[x]].len = t[p].len + 1;
      }
      p = t[p].next[x];
    }
    return p;
  }
  
  void work() {
    std::queue<int> q;
    q.push(1);
    
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      
      for (int i = 0; i < N; i++) {
        if (t[u].next[i] == 0) {
          t[u].next[i] = t[t[u].fail].next[i];
        } else {
          t[t[u].next[i]].fail = t[t[u].fail].next[i];
          t[t[t[u].fail].next[i]].adj.push_back(t[u].next[i]);
          q.push(t[u].next[i]);
        }
      }
    }
  }
  
  int len(int p) {
    return t[p].len;
  }
  
  int fail(int p) {
    return t[p].fail;
  }
  
  const std::vector<int>& adj(int p) {
    return t[p].adj;
  }
  
  int next(int p, int x) {
    return t[p].next[x];
  }
  
  int size() {
    return t.size();
  }
};

void Thephix() {
  int n;
  cin >> n;
  AhoCorasick ac;
  set<int> S;
  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    int x = ac.insert(s);
    S.insert(x);
  }
  ac.work();

  string s;
  cin >> s;
  n = s.size();
  reverse(s.begin(), s.end());
  vector<int> p(n + 1);
  p[0] = 1;
  for (int i = 1; i <= n; ++i) {
    p[i] = ac.next(p[i - 1], s[i - 1] - 'a');
  }
  for (int i = n; i >= 1; --i) {
    if (S.contains(p[i])) {
      int len = ac.len(p[i]);
      string t = s.substr(i - len, len);
      reverse(t.begin(), t.end());
      cout << t << " ";
      i -= len - 1;
    } else {
      cout << s[i - 1] << " ";
    }
  }
  cout << "\n";
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