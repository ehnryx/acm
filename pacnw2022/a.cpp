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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<string> ss(n);
  for(int i=0; i<n; i++) {
    cin >> ss[i];
  }
  sort(begin(ss), end(ss));
  ss.resize(distance(begin(ss), unique(begin(ss), end(ss))));

  map<char, int> remap;
  for(const auto& s : ss) {
    for(char c : s) {
      remap[c];
    }
  }
  static constexpr int M = 18;
  if(size(remap) > M) {
    return void(cout << 0 << nl);
  }

  for(char c='a'; size(remap)<M; c++) {
    remap[c];
  }
  vector<char> cs;
  for(auto& it : remap) {
    it.second = size(cs);
    cs.push_back(it.first);
  }

  vector adj(M, vector(M, false));
  for(const auto& s : ss) {
    for(auto [i, j] : { pair(0, 1), pair(0, 2), pair(1, 2) }) {
      adj[remap[s[i]]][remap[s[j]]] = true;
      adj[remap[s[j]]][remap[s[i]]] = true;
    }
  }
  for(int i=0; i<M; i++) {
    if(adj[i][i]) {
      return void(cout << 0 << nl);
    }
  }

  vector<int> x, y, z;
  auto solve = [&](auto&& self) -> bool {
    const int i = size(x) + size(y) + size(z);
    if(i == 18) return true;
    if(size(x) < 6) {
      bool ok = true;
      for(int j : x) {
        ok &= not adj[i][j];
      }
      if(ok) {
        x.push_back(i);
        if(self(self)) return true;
        x.pop_back();
      }
    }
    if(size(y) < 6) {
      bool ok = true;
      for(int j : y) {
        ok &= not adj[i][j];
      }
      if(ok) {
        y.push_back(i);
        if(self(self)) return true;
        y.pop_back();
      }
    }
    if(size(z) < 6) {
      bool ok = true;
      for(int j : z) {
        ok &= not adj[i][j];
      }
      if(ok) {
        z.push_back(i);
        if(self(self)) return true;
        z.pop_back();
      }
    }
    return false;
  };

  if (solve(solve)) {
    for(int i : x) cout << cs[i];
    cout << " ";
    for(int i : y) cout << cs[i];
    cout << " ";
    for(int i : z) cout << cs[i];
    cout << nl;
  } else {
    cout << 0 << nl;
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
