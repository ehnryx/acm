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
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<n; i++) {
    cin >> b[i];
    if(b[i] < a[i]) swap(a[i], b[i]);
  }
  if(*max_element(begin(a), end(a)) == a.back() and
      *max_element(begin(b), end(b)) == b.back()) {
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
