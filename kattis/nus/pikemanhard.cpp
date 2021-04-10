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

  int n; ll t;
  cin >> n >> t;
  int a, b, c, t0;
  cin >> a >> b >> c >> t0;

  vector<pair<int,int>> order;
  for(int i=0; i<min(n,c); i++) {
    order.emplace_back(t0, 1);
    t0 = ((ll)a * t0 + b) % c + 1;
  }

  n -= min(n, c);
  a = a % c;
  b = (b+1) % c;

  if(a == 1) {
    for(int j=0; j<c; j++) {
      int val = (t0 + (ll)j*b) % c;
      if(val == 0) val += c;
      int cnt = n / c + (j < n % c);
      order.emplace_back(val, cnt);
    }
    sort(order.begin(), order.end());
  } else {
    int len = 0;
    for(int j=1; j<=c; j++) {
      len += (gcd(j, c) == 1);
    }
    for(int j=0, aj=1, sum=0; j<len; j++) {
      int val = ((ll)aj * t0 + (ll)b * sum) % c;
      if(val == 0) val += c;
      int cnt = n / len + (j < n % len);
      order.emplace_back(val, cnt);
      sum = (sum + aj) % c;
      aj = (ll)aj * a % c;
    }
    sort(order.begin(), order.end());
  }

  int num = 0;
  ll penalty = 0;
  ll cur = 0;
  for(auto [val, cnt] : order) {
    ll fit = t / val;
    fit = min(fit, (ll)cnt);
    t -= val * fit;
    num += fit;
    ll add = (cur * fit + (fit*(fit+1)/2) % MOD * val) % MOD;
    penalty += add;
    cur = (cur + val * fit) % MOD;
  }
  cout << num << " " << penalty % MOD << nl;

  return 0;
}
