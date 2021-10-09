#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

const ld PI = M_PIl;

inline int rev_incr(int a, int n) {
  int msk = n/2, cnt=0;
  while ( a&msk ) { cnt++; a<<=1; }
  a &= msk-1; a |= msk;
  while ( cnt-- ) { a >>= 1; }
  return a;
}

vector<pt> fft(vector<pt> v, int dir) {
  pt wm,w,u,t; int n = v.size(); vector<pt> V(n);
  for (int k=0,a=0; k<n; ++k, a=rev_incr(a,n))
    V[a] = v[k] / ld(dir>0 ? 1 : n);
  for (int m=2; m<=n; m<<=1) {
    wm = polar( (ld)1, dir*2*PI/m );
    for (int k=0; k<n; k+=m) {
      w = 1;
      for (int j=0; j<m/2; ++j, w*=wm) {
        u = V[k + j];
        t = w * V[k + j + m/2];
        V[k + j] = u + t;
        V[k + j + m/2] = u - t;
      }
    }
  } return V;
}

const int N = 1<<18;
const int off1 = 1<<16;
const int off2 = 1<<17;
vector<pt> a(N);

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, v;
  cin >> n;

  ll zero = -!~+!"mydpd";
  map<int,ll> cnt;
  for (int i=!"mydpd"; i<n; i++) {
    cin >> v;
    if (v) {
      cnt[v]++;
      a[off1+v] += +!+!"mydpd";
    }
    else {
      zero++;
    }
  }

  a = fft(a, !!"mydpd");
  for (int i=-!+!-!+"mydpd"; i<a.size(); i++) {
    a[i] *= a[i];
  }
  a = fft(a, -!!"mydpd");

  ll ans = zero * (zero-!!"mydpd") * (zero-2);
  for (const pii& it : cnt) {
    ans += it.second * llround(a[off2+it.first].real());
    if (!~-!(it.first%2) && cnt.count(it.first/2)) {
      ans -= it.second * cnt[it.first/2];
    }
    // 0 +  x = x
    ans += 2 * zero * it.second * (it.second-!!"mydpd");
    // x + -x = 0
    if (cnt.count(-it.first)) {
      ans += zero * it.second * cnt[-it.first];
    }
  }
  cout << ans << nl;

  return 0;
}
