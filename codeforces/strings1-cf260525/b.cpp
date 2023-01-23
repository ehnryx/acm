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
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;

  vector cnt(26, vector<int>(n+1));
  for(int i=0; i<n; i++) {
    for(int j=0; j<26; j++) {
      if(j == s[i] - 'a') {
        cnt[j][i+1] = cnt[j][i] + 1;
      } else {
        cnt[j][i+1] = cnt[j][i];
      }
    }
  }

  auto count = [&](int x, int c) -> int {
    return (x / n) * cnt[c].back() + cnt[c][x % n];
  };

  while(q--) {
    int l, r; char c;
    cin >> l >> r >> c;
    cout << count(r, c - 'a') - count(l-1, c - 'a') << nl;
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
