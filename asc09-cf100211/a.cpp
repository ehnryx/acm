//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "chip"

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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
  ll n, d;
  Frac(ll a, ll b=1) {
    ll g = abs(__gcd(a, b));
    n = a/g;
    d = b/g;
    if(d < 0) {
      n = -n;
      d = -d;
    }
  }
  Frac operator + (const Frac& o) const {
    return Frac(n*o.d + d*o.n, d*o.d);
  }
  Frac operator - (const Frac& o) const {
    return Frac(n*o.d - d*o.n, d*o.d);
  }
};

struct Point {
  Frac x, y;
  Point(const Frac& a, const Frac& b): x(a), y(b) {}
};

ostream& operator << (ostream& os, const Frac& v) {
  return os << v.n << "/" << v.d;
}

ostream& operator << (ostream& os, const Point& v) {
  return os << v.x << " " << v.y;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<bool> seen(n);
  for(int i=0; i<n; i++) {
    int o;
    cin >> o;
    seen[--o] = true;
    Frac top = Frac(-1) + Frac(i, n);
    Frac bot = Frac(2) - Frac(i, n);
    Frac tdent = Frac(0) + Frac(i, 3*n);
    Frac bdent = Frac(1) - Frac(i, 3*n);

    vector<Point> path;
    path.emplace_back(Frac(i), Frac(0));
    path.emplace_back(Frac(i), top);
    for(int j=i-1; j>=0; j--) {
      path.emplace_back(Frac(j) + Frac(i, 3*n), top);
      path.emplace_back(Frac(j) + Frac(i, 3*n), tdent);
      path.emplace_back(Frac(j) - Frac(i, 3*n), tdent);
      path.emplace_back(Frac(j) - Frac(i, 3*n), top);
    }
    path.emplace_back(Frac(-7) + Frac(i, n), top);
    path.emplace_back(Frac(-7) + Frac(i, n), bot);
    for(int j=0; j<o; j++) {
      if(!seen[j]) continue;
      path.emplace_back(Frac(j) - Frac(i, 3*n), bot);
      path.emplace_back(Frac(j) - Frac(i, 3*n), bdent);
      path.emplace_back(Frac(j) + Frac(i, 3*n), bdent);
      path.emplace_back(Frac(j) + Frac(i, 3*n), bot);
    }
    path.emplace_back(Frac(o), bot);
    path.emplace_back(Frac(o), Frac(1));

    cout << (int)path.size() - 1 << nl;
    for(const Point& it : path) {
      cout << it << nl;
    }
  }

  return 0;
}
