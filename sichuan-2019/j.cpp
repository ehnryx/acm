//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9 + 7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

void solve() {
  static const int M = 2600;
  static map<int,int> rev;
  for(static int i=0; i<M; i++) {
    rev[3 * (i*(i+1)/2)] = i;
  }
  static vector<ll> fact(3*M), invf(3*M);
  fact[0] = invf[0] = 1;
  for(static int i=1; i<3*M; i++) {
    fact[i] = fact[i-1] * i % MOD;
    invf[i] = power(fact[i], MOD-2, MOD);
  }

  static function<ll(int,int)> choose = [=](int n, int r) -> ll {
    if(r < 0 || r > n) return 0;
    return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
  };

  int n;
  cin >> n;
  int m = sqrt(2*n/3) + 7;
  int best = INF;
  int all = 0;
  for(int i=0; i<m; i++) {
    int si = i + 3 * (i*(i-1)/2);
    if(si > n) break;
    for(int j=0; j<m; j++) {
      int sj = 2*j + 3 * (j*(j-1)/2);
      if(si + sj > n) break;
      if(!rev.count(n - (si + sj))) continue;
      int k = rev[n - (si + sj)];
      //cerr << "add @ " << i << " " << j << " " << k << nl;
      int tot = i + j + k;
      best = min(best, tot);
      all = (all + choose(tot, i) * choose(tot-i, j)) % MOD;
    }
  }
  cout << best << " " << all << nl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";
    solve();
  }

  return 0;
}
