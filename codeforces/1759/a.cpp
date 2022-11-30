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


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string s;
  cin >> s;
  vector<vector<char>> c(3);
  for(int i=0; i<size(s); i++) {
    c[i % 3].push_back(s[i]);
  }
  for(int i=0; i<3; i++) {
    c[i].resize(distance(begin(c[i]), unique(begin(c[i]), end(c[i]))));
    if(size(c[i]) > 1) {
      return void(cout << "NO" << nl);
    }
  }

  if(
      ((empty(c[0]) or c[0].back() == 'Y') and
        (empty(c[1]) or c[1].back() == 'e') and
        (empty(c[2]) or c[2].back() == 's')) or
      ((empty(c[0]) or c[0].back() == 's') and
       (empty(c[1]) or c[1].back() == 'Y') and
       (empty(c[2]) or c[2].back() == 'e')) or
      ((empty(c[0]) or c[0].back() == 'e') and
       (empty(c[1]) or c[1].back() == 's') and
       (empty(c[2]) or c[2].back() == 'Y')) ) {
    cout << "YES" << nl;
  } else {
    cout << "NO" << nl;
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
