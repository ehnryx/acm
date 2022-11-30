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
  int n, q;
  cin >> n >> q;
  set<int> bad;
  bad.insert(2*n + 1);
  while(q--) {
    char t;
    cin >> t;
    if(t == '+') {
      int x;
      cin >> x;
      bad.erase(x);
      bad.erase(x + n);
    } else if(t == '-') {
      int x;
      cin >> x;
      bad.insert(x);
      bad.insert(x + n);
    } else {
      int a, b;
      cin >> a >> b;
      if(a > b) swap(a, b);
      if(*bad.lower_bound(a) > b or *bad.lower_bound(b) > a + n) {
        cout << "possible" << nl;
      } else {
        cout << "impossible" << nl;
      }
    }
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
