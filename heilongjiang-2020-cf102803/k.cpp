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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

void sad() {
  cout << 0 << nl;
  exit(0);
}

ll inverse(ll n) {
  ll r = 1;
  for(int e=MOD-2; e; e/=2, n = n*n % MOD) {
    if(e&1) r = r*n % MOD;
  } return r;
}

const int M = 2e5 + 7;
ll fact[M], invf[M];
ll choose(int n, int r) {
  if(r < 0 || n < r) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  fact[0] = invf[0] = 1;
  for(int i=1; i<M; i++) {
    fact[i] = i * fact[i-1] % MOD;
    invf[i] = inverse(fact[i]);
  }

  int n;
  cin >> n;
  map<int,vector<int>> row;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    row[a].push_back(b);
  }

  int sum = 0;
  ll ans = 1;
  for(auto& [d, v] : row) {
    if(d > 1 && !row.count(d-1)) sad();
    sort(begin(v), end(v));
    int m = size(v);
    ll cnt = 1;
    for(int i=0; i<m; i++) {
      v[i] = min(m, v[i] - sum);
      if(v[i] <= i) sad();
      cnt = cnt * (v[i] - i) % MOD;
    }
    //cerr << "orderings: " << cnt << nl;
    sum += m;

    int k = max(1, (int)size(row[d-1]));
    ans = ans * choose(m+k-1, k-1) % MOD * cnt % MOD;
  }
  cout << ans << nl;

  return 0;
}
