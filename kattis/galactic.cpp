#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    ll g = __gcd(a,b);
    n = a/g; d = b/g;
    if(d<0) {
      n = -n; d = -d;
    } else if(d==0) {
      n = abs(n);
    }
  }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
  }
  Frac operator * (const Frac& o) const {
    return Frac(n*o.n, d*o.d);
  }
  Frac operator + (const Frac& o) const {
    return Frac(n*o.d + d*o.n, d*o.d);
  }
  Frac operator - (const Frac& o) const {
    return Frac(n*o.d - d*o.n, d*o.d);
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int m,n;
  cin>>m>>n;
  map<Frac,set<Frac>> cnt;
  int done = 0;
  for(int i=0;i<n;i++) {
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    Frac slope(b-d,a-c);
    Frac intercept = a;
    if(a!=c) intercept = Frac(b) - slope*a;
    if(!cnt[slope].count(intercept)) {
      done += 2;
      cnt[slope].insert(intercept);
    }
  }
  if(cnt.size() == 1) {
    if(m<=done/2+1) cout<<0<<nl;
    else if(m<=done+2) cout<<1<<nl;
    else cout<<max(0,m-done+1)/2<<nl;
  } else {
    cout<<max(0,m-done+1)/2<<nl;
  }

  return 0;
}
