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

namespace ubc {
ll egcd(ll a, ll b, ll& x, ll &y) { if (!b) {x=1; y=0; return a;}
  // to ensure d>=0: x=sgn(a);y=0;return abs(a);       ^^^^^^^^
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }

// Assuming a != 0, find smallest y >= 0 such that ax+by=c (if possible)
bool canon_egcd(ll a, ll b, ll c, ll& x, ll& y) {
  ll d = egcd(a, b, x, y), z = abs(a/d); if (c%d) return false;
  y = (y*(c/d)%z + z)%z, x = (c - b*y)/a; return true; }
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int r, s, n;
  cin >> r >> s >> n;
  vector<int> a(r), b(s), cap(n);
  for(int i=0; i<r; i++) {
    cin >> a[i];
  }
  for(int i=0; i<s; i++) {
    cin >> b[i];
  }
  for(int i=0; i<n; i++) {
    cin >> cap[i];
  }
  vector<int> sa(size(a) + 1), sb(size(b) + 1);
  partial_sum(begin(a), end(a), begin(sa) + 1);
  partial_sum(begin(b), end(b), begin(sb) + 1);
  assert(sa.back() == accumulate(begin(a), end(a), 0));
  assert(sb.back() == accumulate(begin(b), end(b), 0));

  static constexpr int M = 2e6 + 1;
  vector<bool> possible(M);
  for(int i=0; i<M; i++) {
    if(ll x, y; ubc::canon_egcd(sa.back(), sb.back(), i, x, y) and
        x >= 0 and y >= 0) {
      possible[i] = true;
    }
  }

  auto diff = [&](const vector<int>& ps, int i, int j) {
    if(i <= j) return ps[j] - ps[i];
    return ps[j] + ps.back() - ps[i];
  };

  vector dp(r, vector<bool>(s));
  dp[0][0] = true;
  for(int t=0; t<n; t++) {
    vector ndp(r, vector<bool>(s));
    for(int i=0; i<r; i++) {
      for(int j=0; j<s; j++) {
        if(not dp[i][j]) continue;
        for(int ni=0; ni<r; ni++) {
          for(int nj=0; nj<s; nj++) {
            if(ndp[ni][nj]) continue;
            int d = diff(sa, i, ni) + diff(sb, j, nj);
            ndp[ni][nj] = (d <= cap[t] and possible[cap[t] - d]);
          }
        }
      }
    }
    dp = move(ndp);
  }

  for(int i=0; i<r; i++) {
    for(int j=0; j<s; j++) {
      if(dp[i][j]) {
        return void(cout << "Yes" << nl);
      }
    }
  }
  cout << "No" << nl;
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
