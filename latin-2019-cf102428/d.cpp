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
    ll g = abs(__gcd(a,b));
    n = a/g; d = b/g;
    if(d<0) { n = -n; d = -d; }
  }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
  }
  Frac operator + (const Frac& o) const {
    return Frac(n*o.d + d*o.n, d*o.d);
  }
  Frac operator * (const Frac& o) const {
    return Frac(n*o.n, d*o.d);
  }
};

ostream& operator << (ostream& os, const Frac& v) {
  return os << v.n << "/" << v.d;
}

const int BIG = 1e5;
const int N = 1e3+1;
const int O = 1e4+1;
int x[N], y[N], b[N];

Frac intersect(int i, int j) {
  return Frac(y[j]-y[i], x[i]-x[j]);
}

Frac eval(int i, const Frac& v) {
  return v * x[i] + y[i];
}

// (a,b) -> y = ax+b
bool solve(int n) {
  Frac lb = Frac(-BIG);
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      if(b[i] >= b[j]) continue;
      if(x[i] < x[j]) {
        lb = max(lb, intersect(i,j));
      } else if(x[i] > x[j]) {
      } else {
        if(y[i] > y[j]) return false;
      }
    }
  }
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      if(b[i] >= b[j]) continue;
      if(eval(j,lb) < eval(i,lb)) return false;
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i] >> b[i];
    x[i] += O;
    y[i] += O;
  }

  // (a,b) -> y = ax+b
  bool ans = false;
  ans |= solve(n);
  for(int i=0;i<n;i++) {
    x[i] = -x[i];
    y[i] = -y[i];
  }
  ans |= solve(n);
  for(int i=0;i<n;i++) {
    swap(x[i],y[i]);
  }
  ans |= solve(n);
  for(int i=0;i<n;i++) {
    x[i] = -x[i];
    y[i] = -y[i];
  }
  ans |= solve(n);

  if(ans) {
    cout << "Y" << nl;
  } else {
    cout << "N" << nl;
  }

  return 0;
}
