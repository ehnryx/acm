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

  vector<int> fib = {0, 1};
  while(fib.back() <= n) {
    fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
  }

  // ...bbbcccdddeee.bbccddee.bcde$
  vector cnt(2, vector<ll>(4));
  fill(begin(cnt[1]), end(cnt[1]), 1);
  for(int i=2; cnt[i-1][0]<pow(n,3./4); i++) {
    cnt.emplace_back(4);
    const int f = fib[i];
    cnt[i][0] = f*f*f*cnt[i-1][3] + f*f*cnt[i-1][2] + f*cnt[i-1][1] + cnt[i-1][0];
    cnt[i][1] = f*f*cnt[i-1][3] + f*cnt[i-1][2] + cnt[i-1][1];
    cnt[i][2] = f*cnt[i-1][3] + cnt[i-1][2];
    cnt[i][3] = cnt[i-1][3];
  }

  string ans;
  for(int i=size(cnt)-1; i>0; i--) {
    while(cnt[i][0] <= n) {
      n -= cnt[i][0];
      ans.push_back('a');
    }
    if(not empty(ans)) {
      ans += string(fib[i], 'b');
      ans += string(fib[i], 'c');
      ans += string(fib[i], 'd');
    }
  }
  cout << ans << " abcd" << nl;
  cerr << "length = " << size(ans) << endl;
  assert(size(ans) <= 200);
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
