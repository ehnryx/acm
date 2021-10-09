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
  bool operator < (const Frac& o) const { return value() < o.value(); }
  Frac operator + (const Frac& o) const { return Frac(n*o.d + d*o.n, d*o.d); }
  Frac operator - (const Frac& o) const { return Frac(n*o.d - d*o.n, d*o.d); }
  Frac operator * (const Frac& o) const { return Frac(n*o.n, d*o.d); }
  ld value() const { return (ld)n/d; }
  ll floor() const { return n/d; }
};

namespace CF {
  typedef long double d; // for N ~ 1e7; long double for N ~ 1e9
  pair<ll, ll> approximate(d x, ll N) {
    ll LP = 0, LQ = 1, P = 1, Q = 0, inf = LLONG_MAX; d y = x;
    for (;;) {
      ll lim = min(P ? (N-LP) / P : inf, Q ? (N-LQ) / Q : inf),
         a = (ll)floor(y), b = min(a, lim),
         NP = b*P + LP, NQ = b*Q + LQ;
      if (a > b) {
        // If b > a/2, we have a semi-convergent that gives us a
        // better approximation; if b = a/2, we *may* have one.
        // Return {P, Q} here for a more canonical approximation.
        return (abs(x - (d)NP / (d)NQ) < abs(x - (d)P / (d)Q)) ?
          make_pair(NP, NQ) : make_pair(P, Q);
      }
      if (abs(y = 1/(y - (d)a)) > 3*N) {
        return {NP, NQ};
      }
      LP = P; P = NP;
      LQ = Q; Q = NQ;
    }
  }
}

// assume 0 <= x < 1
pair<ll, ll> approximate(ld x, ll N) {
  ll op = 1, oq = 0, p = 0, q = 1, a = 0;
  for(ld y = 1/x; ; y = 1/(y-a)) {
    if(abs(y) > 3*N) return make_pair(p, q);
    a = floor(y);
    if(q > (N - oq) / a) {
      ll t = (N - oq) / q;
      ll tp = t*p + op, tq = t*q + oq;
      ld A = (ld)p/q, B = (ld)tp/tq;
      return abs(A-x) < abs(B-x) ? make_pair(p, q) : make_pair(tp, tq);
    }
    op += p*a; swap(op, p);
    oq += q*a; swap(oq, q);
  }
}

void caseinit() {
}

void casesolve() {
  caseinit();

  int n;
  cin >> n;
  int a[n], b[n];
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
  }

  Frac lb(0, 1), ub(2*INF, 1);
  for(int i=0; i<n; i++) {
    for(int j=0; j<i; j++) {
      if(b[j] - b[i] == 0) {
        if(a[i] - a[j] <= 0) {
          cout << "IMPOSSIBLE" << nl;
          return;
        }
      } else {
        Frac cur(a[i] - a[j], b[j] - b[i]);
        if(b[j] - b[i] > 0) {
          ub = min(ub, cur);
        } else {
          lb = max(lb, cur);
        }
      }
    }
  }
  if(!(lb < ub)) {
    cout << "IMPOSSIBLE" << nl;
    return;
  }

  Frac mid = (lb + ub) * Frac(1, 2);
  Frac f(mid.floor(), 1);
  Frac goal = mid - f;
  ll l = 1;
  ll r = 2*INF;
  while(l < r) {
    ll m = (l+r)/2;
    ll N, D;
    tie(N, D) = approximate(goal.value(), m);
    Frac cur = Frac(N, D) + f;
    if(lb < cur && cur < ub) {
      r = m;
    } else {
      l = m+1;
    }
  }

  ll bot = approximate(goal.value(), r).second;
  ll top = (bot * lb.n) / lb.d + 1;
  cout << bot << " " << top << nl;

  return;
}

