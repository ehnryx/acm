#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos(-1.L);

typedef complex<ld> Complex;

// *** Fast Fourier Transform (Iterative) ***
// Reverse-bitmasking adder. rev_incr(a,n) returns REV(REV(a)+1)
inline int rev_incr(int a, int n) { int msk = n/2, cnt=0;
  while ( a&msk ) { cnt++; a<<=1; }
  a &= msk-1; a |= msk;
  while ( cnt-- ) a >>= 1;
  return a; }
// Compute in V the discrete fourier transform of v
// dir=1: forward transform, evaluates polynomial at complex roots of unity
// dir=-1: inverse transform, interpolates point-value form to coefficients
vector<Complex> FFT(vector<Complex> v, int dir=1) {
  Complex wm,w,u,t; int n = v.size(); vector<Complex> V(n);
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
      } } } return V; 
}

const int N = 1<<20;
vector<Complex> r(N,0), g(N,0), b(N,0);
vector<Complex> ir(N,0), ig(N,0), ib(N,0);
vector<Complex> rb(N), br(N), rg(N), gr(N), gb(N), bg(N);

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  for (int i=0; i<n; i++) {
    switch (s[i]) {
      case 'R': r[i] = 1;
            ir[n-i] = 1;
            break;
      case 'B': b[i] = 1;
            ib[n-i] = 1;
            break;
      default:  g[i] = 1;
            ig[n-i] = 1;
            break;
    }
  }

  r = FFT(r);
  b = FFT(b);
  g = FFT(g);
  ir = FFT(ir);
  ib = FFT(ib);
  ig = FFT(ig);

  for (int i=0; i<N; i++) {
    rb[i] = r[i] * ib[i];
    br[i] = b[i] * ir[i];
    rg[i] = r[i] * ig[i];
    gr[i] = g[i] * ir[i];
    bg[i] = b[i] * ig[i];
    gb[i] = g[i] * ib[i];
  }

  rb = FFT(rb, -1);
  br = FFT(br, -1);
  rg = FFT(rg, -1);
  gr = FFT(gr, -1);
  bg = FFT(bg, -1);
  gb = FFT(gb, -1);

  map<int,int> ans;
  vector<pii> diff;

  diff.push_back(pii(-1,0));
  for (int i=1; i<n; i++) {
    int cnt = 0;
    cnt += llround(rb[n+i].real()) + llround(rb[2*n-i].real());
    cnt += llround(br[n+i].real()) + llround(br[2*n-i].real());
    cnt += llround(rg[n+i].real()) + llround(rg[2*n-i].real());
    cnt += llround(gr[n+i].real()) + llround(gr[2*n-i].real());
    cnt += llround(bg[n+i].real()) + llround(bg[2*n-i].real());
    cnt += llround(gb[n+i].real()) + llround(gb[2*n-i].real());
    diff.push_back(pii(cnt, (n-i)%n));
    if (ans.count(cnt)) ans[cnt] = min(ans[cnt], (n-i)%n);
    else ans[cnt] = (n-i)%n;
    //cerr << i << ": " << diff[i].first << " " << diff[i].second << nl;
  }

  auto cmp = [&] (const pii& a, const pii& b) {
    if (a.first == b.first) return a.second < b.second;
    else return a.first < b.first;
  };
  sort(diff.begin(), diff.end(), cmp);

  assert(ans.count(diff[k].first));
  cout << ans[diff[k].first] << nl;

  return 0;
}
