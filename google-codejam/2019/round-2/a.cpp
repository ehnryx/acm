//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



void init() {
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    ll g = abs(__gcd(a, b));
    n = a/g; d = b/g;
    if(d<0) { n = -n; d = -d; }
  }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
  }
};

void caseinit() {
}

void casesolve() {
  caseinit();

  int n;
  cin >> n;
  vector<pair<int,int>> p;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    p.push_back(make_pair(a, b));
  }

  set<Frac> seen;
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      Frac x(p[j].second - p[i].second, p[i].first - p[j].first);
      if(x.d == 0) continue;
      if(x.n > 0) {
        seen.insert(x);
      }
    }
  }
  cout << seen.size() + 1 << nl;

  return;
}

