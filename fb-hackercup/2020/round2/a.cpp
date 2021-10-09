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



int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

vector<int> read(int n, int k) {
  vector<int> r(n+1);
  for(int i=1; i<=k; i++) {
    cin >> r[i];
  }
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  for(int i=k+1; i<=n; i++) {
    r[i] = (a*r[i-2] + b*r[i-1] + c) % d;
  }
  return r;
}

void casesolve() {

  int n, k;
  cin >> n >> k;
  vector<int> s = read(n, k);
  vector<int> x = read(n, k);
  vector<int> y = read(n, k);

  ll lmin = 0, lmax = 0;
  ll rmin = 0, rmax = 0;
  for(int i=1; i<=n; i++) {
    if(s[i] < x[i]) {
      lmin += x[i] - s[i];
    } else {
      rmax += s[i] - x[i];
    }
    if(s[i] < x[i] + y[i]) {
      lmax += x[i] + y[i] - s[i];
    } else {
      rmin += s[i] - (x[i] + y[i]);
    }
  }

  if(lmax < rmin || rmax < lmin) {
    cout << -1 << nl;
  } else {
    cout << max(lmin, rmin) << nl;
  }

  return;
}

