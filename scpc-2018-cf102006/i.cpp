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
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int D = 2;
typedef vector<ld> ndpt;
typedef list<ndpt>::iterator It;
struct Miniball { list<ndpt> L; int m; vector<vector<ld> > v, a; vector<ndpt> c;
  ndpt q0; vector<ld> r2, z, f; It end; ndpt c_c; ld c_r2;
  Miniball() : m(0),v(D+1,vector<ld>(D)),a(D+1,vector<ld>(D)),c(D+1,ndpt(D,0)),
    q0(D), r2(D+1), z(D+1), f(D+1), end(L.begin()), c_c(c[0]), c_r2(-1.L) {}
  void add(ndpt &p) { L.push_back(p); }
  void move_to_front(It i) { m--; if (end==i) end++; L.splice(L.begin(),L,i); }
  void mtf_mb(It i) { end=L.begin(); if (m==D+1) return;
    for (It k=L.begin(),j;(j=k++)!=i;) { ld e = get_e(j);
      if (e > 0 && push(*j)) mtf_mb(j), move_to_front(j); } }
  void pivot_mb(It i) {
    It t=++L.begin(), pivot; mtf_mb(t); ld max_e, old_r2=-1;
    do { if((max_e=max_excess(t,i,pivot)) > 0) {
      if ((t=end)==pivot) ++t;
      old_r2=c_r2; push(*pivot); mtf_mb(end); move_to_front(pivot); }
    } while (max_e > 0 && c_r2 > old_r2); }
  ld max_excess(It j,It i,It& pivot) { ld max_e=0,e;
    for (; j!=i;++j) if ((e=get_e(j)) > max_e) max_e=e,pivot=j; return max_e; }
  ld get_e(It j) { ld e=-c_r2; for (int i=0;i<D;++i) e+=pow((*j)[i]-c_c[i], 2);
    return e; }
  bool push(const ndpt& p) { int i, j; if (!m) c[0]=q0=p, r2[0]=0; else {
      for (i=0;i<D;++i) v[m][i]=p[i]-q0[i];
      for (i=1;i<m;++i) { a[m][i]=0;
        for (j=0;j<D;++j) a[m][i]+=v[i][j]*v[m][j];
        a[m][i]*=(2/z[i]); }
      for (i=1;i<m;++i) for (j=0;j<D;++j) v[m][j]-=a[m][i]*v[i][j];
      z[m]=0; for (j=0;j<D;++j) z[m]+=2*pow(v[m][j], 2);
      if (z[m] < c_r2*EPS) return false;
      ld e=-r2[m-1]; for (i=0;i<D;++i) e+=pow(p[i]-c[m-1][i], 2);
      f[m]=e/z[m];
      for (i=0;i<D;++i) c[m][i]=c[m-1][i]+f[m]*v[m][i];
      r2[m]=r2[m-1]+e*f[m]/2;
    } c_c=c[m]; c_r2=r2[m]; m++; return true; }
  void build(){ pivot_mb(L.end()); }
};

ndpt to_ndpt(const pt& v) {
  return { v.real(), v.imag() };
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#define FILENAME "robots"
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
#endif

  int T;
  cin >> T;
  while (T--) {

    int n, R, r;
    cin >> n >> R >> r;

    Miniball mb;
    vector<ndpt> p;
    pt cur(0,0);
    p.push_back(to_ndpt(cur));
    mb.add(p.back());
    for (int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      cur += pt(x,y);
      p.push_back(to_ndpt(cur));
      mb.add(p.back());
    }
    mb.build();
    cout << -mb.c_c[0] << " " << -mb.c_c[1] << nl;

  }

  return 0;
}
