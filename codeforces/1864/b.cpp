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
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  if(m % 2 == 0 and m < n) {
    sort(begin(s), end(s));
    cout << s << nl;
  } else {
    string even, odd;
    for(int i=0; i<n; i++) {
      (i % 2 ? odd : even).push_back(s[i]);
    }
    sort(begin(even), end(even));
    sort(begin(odd), end(odd));
    if(m % 2 == 0 and m == n and odd < even) {
      swap(even, odd);
    }
    for(int i=0, ei=0, oi=0; i<n; i++) {
      if(i % 2 == 0) {
        cout << even[ei++];
      } else {
        cout << odd[oi++];
      }
    }
    cout << nl;
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
