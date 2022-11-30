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
  string all(26, 0);
  iota(begin(all), end(all), 'a');
  cout << "? " << all << endl;
  int n;
  cin >> n;
  for(int i=0, _; i<n; i++) {
    cin >> _;
  }

  vector<vector<int>> one(5);
  for(int i=0; i<5; i++) {
    string s;
    for(int j=0; j<26; j++) {
      if(j >> i & 1) {
        s.push_back(j + 'a');
      }
    }
    cout << "? " << s << endl;
    int res;
    cin >> res;
    one[i].resize(res);
    for(int j=0; j<res; j++) {
      cin >> one[i][j];
    }
  }

  string ans(n, 0);
  for(int j=0; j<26; j++) {
    vector<int> cur(n);
    iota(begin(cur), end(cur), 1);
    for(int i=0; i<5; i++) {
      vector<int> nxt;
      if(j >> i & 1) {
        set_intersection(begin(cur), end(cur), begin(one[i]), end(one[i]), back_inserter(nxt));
      } else {
        set_difference(begin(cur), end(cur), begin(one[i]), end(one[i]), back_inserter(nxt));
      }
      cur = nxt;
    }
    for(int i : cur) {
      ans[i-1] = j + 'a';
    }
  }
  cout << "! " << ans << endl;
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
