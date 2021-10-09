#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "zanzibar"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
  ll n, d;
  Frac(ll a, ll b) {
    ll g = __gcd(a,b);
    n = a/g; d = b/g;
  }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
  }
  bool operator == (const Frac& o) const {
    return n*o.d == d*o.n;
  }
  Frac operator - (const Frac& o) const {
    return Frac(n*o.d - d*o.n, d*o.d);
  }
  Frac operator + (const Frac& o) const {
    return Frac(n*o.d + d*o.n, d*o.d);
  }
  Frac fabs() const {
    return Frac(abs(n), abs(d));
  }
  void print() const {
    cout << n << "/" << d << nl;
  }
};

namespace std {
  template<> struct hash<Frac> {
    size_t operator () (const Frac& v) const {
      return v.d<<10 ^ v.n;
    }
  };
}

const int N = 360360+1;
bool valid[N];
vector<Frac> vals;

void solve() {
  int a, b;
  cin >> a >> b;

  if (a == 0) {
    cout << "0/1" << nl;
  } else {
    Frac cur = Frac(a,b);
    auto it = lower_bound(vals.begin(), vals.end(), cur);
    min((cur-*it).fabs(),(cur-*prev(it)).fabs()).print();
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(TESTFILE ".in", "r", stdin);
#endif

  vector<int> trans;
  for (int i=2; i<=13; i++) {
    trans.push_back(360360/i);
  }

  vals.push_back(Frac(0,1));
  valid[0] = true;
  for (int i=1; i<N; i++) {
    for (int j : trans) {
      if (i-j>=0) valid[i] |= valid[i-j];
    }
    if (valid[i]) vals.push_back(Frac(i,360360));
  }
  //cerr << "SIZE: " << vals.size() << nl;

  int T;
  cin >> T;

  for (int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";
    solve();
  }

  return 0;
}
