#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/aho_corasick.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct to_int {
  int operator()(char c) const { return c - 'a'; }
  static constexpr int size = 26;
};
using KMP = aho_corasick<char, to_int>;
//using KMP = aho_corasick<char>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  string text;
  cin >> text;
  int m;
  cin >> m;
  vector<string> orig(m);
  unordered_set<string> seen;
  KMP& kmp = *(new KMP);  // 140ms faster because skips destruction
  for(int i=0; i<m; i++) {
    cin >> orig[i];
    string s;
    s.reserve(size(orig[i]));
    transform(rbegin(orig[i]), rend(orig[i]), back_inserter(s),
        [](char c) { return tolower(c); });
    if(seen.insert(s).second) {
      kmp.add(s);  // don't duplicate
      orig[size(seen) - 1] = orig[i];
    }
  }
  kmp.build();

  vector<vector<int>> jump(n);
  kmp.find_all(text, [&](int pattern, int index) {
      jump[index + 1 - size(orig[pattern])].push_back(pattern); });

  vector<int> back(n+1, -1);
  queue<int> bfs;
  bfs.push(0);
  back[0] = 0;
  while(not empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    if(u == n) break;
    for(int i : jump[u]) {
      int to = u + size(orig[i]);
      if(back[to] == -1) {
        back[to] = i;
        bfs.push(to);
      }
    }
  }
  assert(back[n] != -1);

  vector<string> ans;
  for(int u = n; u > 0; u -= size(orig[back[u]])) {
    ans.push_back(orig[back[u]]);
  }
  for(auto s : ans | views::reverse) {
    cout << s << " ";
  }
  cout << nl;
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
