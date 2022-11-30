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
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  int g = 0;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    g = gcd(g, a[i]);
  }
  for(int i=0; i<n; i++) {
    a[i] /= g;
  }

  static constexpr int M = 4e7;
  vector<bool> valid(M);
  valid[0] = true;
  for(int i=0; i<M; i++) {
    for(int x : a) {
      if(x <= i and valid[i - x]) {
        valid[i] = true;
      }
    }
  }

  vector<int> possible;
  for(int i=1; i<M; i++) {
    if(valid[i]) {
      possible.push_back(i);
    }
  }

  //const int prefix = size(possible);
  //const int prefix = 1e4;

  vector<ll> b(m);
  vector<bool> ans(m);
  for(int i=0; i<m; i++) {
    cin >> b[i];
    if(b[i] % g != 0) {
      continue;
    }
    b[i] /= g;

    if(b[i] < M) {
      ans[i] = valid[b[i]];
    } else {
      static constexpr int T = 1e3;
      for(int bs=0; bs<T; bs++) {
        //int idx = rng() % prefix;
        int idx = bs; // does this work?
        // want bi - guess < M, so guess > bi - M
        ll k = (b[i] - M) / possible[idx] + 1;
        ll guess = k * possible[idx];
        if(guess <= b[i] and valid[b[i] - guess]) {
          ans[i] = true;
          break;
        }
      }
    }
  }

  for(auto x : ans) {
    cout << x << " ";
  }
  cout << nl;
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
