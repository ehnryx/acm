#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/kmp_matching.h"

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
  string s, t;
  cin >> s >> t;
  string r(rbegin(t), rend(t));
  transform(begin(r), end(r), begin(r), [](char c) {
      if(c == 'N' || c == 'S') return c ^ 'N' ^ 'S';
      else return c ^ 'W' ^ 'E'; });

  kmp_matching kmp(r + s);
  if(kmp.fail.back() == -1) {
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
