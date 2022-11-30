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

/*
 * one marking:
 *  C(n, k-1) * (k-1)! --> C(n, k)
 * 
 * m markings:
 *  C(mi, j) * j * C(n-mi, k-j) * (k-1)! --> C(mi, j) * C(n-mi, k-j)
 *  degree: mi - j + 1
 */

ld choose(int n, int k) {
  if(k < 0 or n < k) return 0;
  ld ans = 1;
  for(int i=0; i<k; i++) {
    ans *= n - i;
    ans /= i + 1;
  }
  return ans;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int k, m;
  cin >> k >> m;
  vector<int> ms(m);
  for(int i=0; i<m; i++) {
    cin >> ms[i];
  }
  int n = accumulate(begin(ms), end(ms), 0);

  ld fk = 1;
  for(int i=2; i<k; i++) {
    fk *= i;
  }

  vector<vector<int>> parts;
  auto get_vectors = [&, p=vector<int>()](auto&& self, int have, int i) mutable {
    if(i == size(ms)) {
      if(have == 0) {
        parts.push_back(p);
      }
      return;
    }
    for(int j = 0; j <= min(have, ms[i]); j++) {
      p.push_back(j);
      self(self, have - j, i + 1);
      p.pop_back();
    }
  };
  get_vectors(get_vectors, k, 0);

  ld ans = 0;
  for(auto p : parts) {
    ld sets = 1;
    for(int i=0; i<m; i++) {
      sets *= choose(ms[i], p[i]);
    }
    ld perms = 0;
    for(int down=0; down<m; down++) {
      ld cur = 1;
      for(int i=0; i<m; i++) {
        cur *= choose(ms[i], p[i] - (i == down));
      }
      cur *= fk;
      perms += cur;
    }
    ans += min(perms, sets);
  }

  ans /= choose(n, k);

  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(12);
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
