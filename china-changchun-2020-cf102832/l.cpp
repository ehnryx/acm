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
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll egcd(ll a, ll b, ll& x, ll &y) { if (!b) {x=1; y=0; return a;}
  // to ensure d>=0: x=sgn(a);y=0;return abs(a);       ^^^^^^^^
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d;
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

  ll n, k, s;
  cin >> n >> k >> s;

  if(n == 1) {
    cout << s << nl;
    return 0;
  }

  vector<ll> a(n+k+1);
  for(int i=0; i<=n+k; i++) {
    a[i] = i % (k+1);
  }
  vector<ll> pref(1);
  partial_sum(begin(a), end(a), back_inserter(pref));

  vector<pair<int,int>> order;
  vector<ll> ans;
  ll g = gcd(k+1, n);
  for(int i=0; i<=k; i++) {
    ll lb = pref[i+n] - pref[i];
    //cerr << s << " w/ " << lb << " and " << g << nl;
    if(s < lb || (s - lb) % g) continue;
    ll mod = (k+1) / g;
    ll x, y;
    egcd(n/g, mod, x, y);
    x = (x + mod) % mod; // make positive
    ll add = x*((s-lb)/g % mod) % mod;
    if(add < 0) while(clock()<.8*CLOCKS_PER_SEC);
    assert(add >= 0);
    ll ns = s - lb - add * n;
    assert(ns % (k+1) == 0);
    if(ns >= 0) {
      //cerr << ns << " = " << s << " - " << lb << " - " << add << " * " << n << nl;
      rotate(begin(a), begin(a)+i, end(a));
      for(int j=0; j<n; j++) {
        ans.push_back(a[j] + add);
        //cerr << ans[j] << nl;
        if(j > 0) {
          if(a[j] > a[j-1]) {
            order.emplace_back(j, j);
          } else {
            order.emplace_back(n-j, j);
          }
        }
      }
      //cerr << s << " -> " << ns << nl;
      //assert(s - ns == accumulate(begin(ans), end(ans), (ll)0));
      s = ns;
      break;
    }
  }
  if(ans.empty()) {
    cout << -1 << nl;
    return 0;
  }

  // bring s to <= n*(k+1)
  ll down = s / (n*(k+1));
  s -= down * (k+1) * n;
  //assert(s < n*(k+1));
  //assert(s % (k+1) == 0);
  for(int i=0; i<n; i++) {
    ans[i] += down * (k+1);
  }

  sort(begin(order), end(order), greater<pair<int,int>>());
  for(int i=0; s>0; i++) {
    if(i >= size(order)) while(clock()<.5*CLOCKS_PER_SEC);
    assert(i < size(order));
    if(order[i].first * (k+1) > s) continue;
    s -= order[i].first * (k+1);
    int j = order[i].second;
    if(a[j] > a[j-1]) {
      for(int t=0; t<j; t++) {
        ans[t] += k+1;
      }
    } else {
      for(int t=j; t<n; t++) {
        ans[t] += k+1;
      }
    }
  }

  for(int i=0; i<n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
