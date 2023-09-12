#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "utility/output.h"

%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

Int solve(const vector<int>& v) {
  if(empty(v)) return 0;

  if(v.back() == 0) {
    return Int((int)size(v)) * Int((int)size(v));
  }

  int high_bit = 31 - __builtin_clz(v.back());
  vector<int> left, right;
  for(int i=0; i<size(v); i++) {
    if(v[i] & 1<<high_bit) {
      right.push_back(v[i] ^ 1<<high_bit);
    } else {
      left.push_back(v[i]);
    }
  }

  Int prod = Int((int)size(left)) * Int((int)size(right));
  Int ans = prod * (1 + 2);
  ans += Int((int)size(right)) * Int((int)size(right));
  return ans + solve(left) + solve(right);
}

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> v(n);
  for(int i=0; i<n; i++) {
    cin >> v[i];
  }
  sort(begin(v), end(v));
  Int total = solve(v);
  //cerr << "TOTAL: " << total << nl;
  cout << total / (Int(n) * Int(n)) << nl;
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
