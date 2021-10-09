#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

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
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

ll sqr(ll x) { return x*x; }
ll dist(const pt& a, const pt& b) {
  return sqr(llround(a.real()-b.real())) + sqr(llround(a.imag()-b.imag()));
}

void caseinit() {
}

void solve() {
  caseinit();

  int n, k;
  cin >> n >> k;
  assert(k == 2);

  vector<pt> p;
  For(i,n) {
    int x, y;
    cin >> x >> y;
    p.push_back(pt(x,y));
  }
  reverse(p.begin(), p.end());

  function<bool(int)> goodVertex = [&] (int s) {
    pt a = p[s];
    pt b = p[(s+n/2)%n];
    FOR(i,1,n/2-1) {
      pt l = p[(s+i)%n];
      pt r = p[(s-i+n)%n];
      if (dist(a,l) != dist(a,r)) return false;
      if (dist(b,l) != dist(b,r)) return false;
    }
    return true;
  };

  function<bool(int)> goodEdge = [&] (int s) {
    int o = (s+n/2)%n;
    pt a = p[s]+p[(s+1)%n];
    pt b = p[o]+p[(o+1)%n];
    For(i,n/2) {
      pt l = (ld)2*p[(s+i)%n];
      pt r = (ld)2*p[(s-i+n)%n];
      if (dist(a,l) != dist(a,r)) return false;
      if (dist(b,l) != dist(b,r)) return false;
    }
    return true;
  };

  function<bool(int)> goodEV = [&] (int s) {
    int o = (s+n/2)%n;
    pt a = (ld)2*p[s];
    pt b = p[o]+p[(o+1)%n];
    FOR(i,1,n/2) {
      pt l = (ld)2*p[(s+i)%n];
      pt r = (ld)2*p[(s-i+n)%n];
      if (dist(a,l) != dist(a,r)) return false;
      if (dist(b,l) != dist(b,r)) return false;
    }
    return true;
  };

  if (n%2 == 0) {
    For(i,n) {
      if (goodVertex(i)) {
        int j = (i+n/2)%n;
        cout << "POSSIBLE" << nl;
        cout << llround(p[i].real()) << "/1" << " " << llround(p[i].imag()) << "/1" << " ";
        cout << llround(p[j].real()) << "/1" << " " << llround(p[j].imag()) << "/1" << nl;
        return;
      }
      if (goodEdge(i)) {
        int j = (i+n/2)%n;
        int ni = (i+1)%n;
        int nj = (j+1)%n;
        ll ax = llround(p[i].real()+p[ni].real());
        ll ay = llround(p[i].imag()+p[ni].imag());
        ll bx = llround(p[j].real()+p[nj].real());
        ll by = llround(p[j].imag()+p[nj].imag());
        cout << "POSSIBLE" << nl;
        if (ax%2 == 0) cout << ax/2 << "/1" << " ";
        else cout << ax << "/2" << " ";
        if (ay%2 == 0) cout << ay/2 << "/1" << " ";
        else cout << ay << "/2" << " ";
        if (bx%2 == 0) cout << bx/2 << "/1" << " ";
        else cout << bx << "/2" << " ";
        if (by%2 == 0) cout << by/2 << "/1" << nl;
        else cout << by << "/2" << nl;
        return;
      }
    }
  }

  else {
    For(i,n) {
      if (goodEV(i)) {
        int j = (i+n/2)%n;
        int nj = (j+1)%n;
        ll bx = llround(p[j].real()+p[nj].real());
        ll by = llround(p[j].imag()+p[nj].imag());
        cout << "POSSIBLE" << nl;
        cout << llround(p[i].real()) << "/1" << " " << llround(p[i].imag()) << "/1" << " ";
        if (bx%2 == 0) cout << bx/2 << "/1" << " ";
        else cout << bx << "/2" << " ";
        if (by%2 == 0) cout << by/2 << "/1" << nl;
        else cout << by << "/2" << nl;
        return;
      }
    }
  }

  cout << "IMPOSSIBLE" << nl;

  return;
}

