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
  unordered_map<string, string> remap;
  map<string, int> ans;
  for(int i=0; i<n; i++) {
    string name;
    cin >> name;
    ans[name];
    int m;
    cin >> m;
    for(int j=0; j<m; j++) {
      string s;
      cin >> s;
      remap[s] = name;
    }
  }
  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int cnt;
    string s;
    cin >> cnt >> s;
    ans[remap[s]] += cnt;
  }
  for(auto [name, v] : ans) {
    cout << name << " " << v << nl;
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
