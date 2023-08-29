#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

constexpr int to_int(char c) { return c - 'a'; }

struct aho_corasick {
  static constexpr int A = 26;
  struct node {
    int pattern;
    int child[A];
    node(): pattern(-1) {
      memset(child, -1, sizeof(child));
    }
  };
  vector<node> nodes;

  static constexpr int root = 0;
  int size() const { return nodes.size(); }
  const auto& operator[](int i) const { return nodes[i]; }

  aho_corasick(int n) {
    nodes.reserve(n+1);
    nodes.emplace_back();
  }

  void add(int i, const string& s) {
    int u = root;
    for(char c : s) {
      if(nodes[u].child[to_int(c)] == -1) {
        nodes[u].child[to_int(c)] = nodes.size();
        nodes.emplace_back();
      }
      u = nodes[u].child[to_int(c)];
    }
    nodes[u].pattern = i;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  aho_corasick left(4e6);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    left.add(i, s);
  }
  aho_corasick right(4e6);
  for(int i=0; i<m; i++) {
    string s;
    cin >> s;
    reverse(begin(s), end(s));
    right.add(i, s);
  }

  int q;
  cin >> q;
  bool valid[2001];
  while(q--) {
    string s;
    cin >> s;
    memset(valid, 0, size(s) + 1);
    for(int u=0, i=0; i<size(s); i++) {
      u = left[u].child[to_int(s[i])];
      if(u == -1) break;
      if(left[u].pattern != -1) {
        valid[i+1] = true;
      }
    }
    bool ok = false;
    for(int u=0, i=(int)size(s)-1; i>=0 and not ok; i--) {
      u = right[u].child[to_int(s[i])];
      if(u == -1) break;
      if(right[u].pattern != -1) {
        ok |= valid[i];
      }
    }
    cout << (ok ? "Yes" : "No") << nl;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
