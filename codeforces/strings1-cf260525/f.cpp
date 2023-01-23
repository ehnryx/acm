#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/suffix_array_lcp.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string s;
  cin >> s;
  const int n = size(s);

  suffix_array_lcp sa(s);
  for(int i=1; i<n; i++) {
    if(sa.lcp(0, i) != n-i) continue;
    int r0 = sa.rank[0];
    int ri = sa.rank[i];
    bool good = [&] {
      if(r0-1 >= 0 and r0-1 != ri and sa.lcp(sa[r0-1], i) == n-i) return true;
      if(r0+1 < sa.size() and r0+1 != ri and sa.lcp(sa[r0+1], i) == n-i) return true;
      if(ri-1 >= 0 and ri-1 != r0 and sa.lcp(sa[ri-1], i) == n-i) return true;
      if(ri+1 < sa.size() and ri+1 != r0 and sa.lcp(sa[ri+1], i) == n-i) return true;
      return false;
    }();
    if(good) {
      return void(cout << s.substr(i) << nl);
    }
  }
  cout << "Just a legend" << nl;
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
