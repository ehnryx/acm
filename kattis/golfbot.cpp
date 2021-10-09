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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

typedef pt Complex;

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
    wm = polar( (ld)1, dir*2*M_PIl/m );
    for (int k=0; k<n; k+=m) {
      w = 1;
      for (int j=0; j<m/2; ++j, w*=wm) {
        u = V[k + j];
        t = w * V[k + j + m/2];
        V[k + j] = u + t;
        V[k + j + m/2] = u - t;
      } } } return V; }
//! See problem 30-6 in CLRS for more details on the integer FFT
//! hints for integer version:
//! 440564289 and 1713844692 are inverses and 2^27th roots of 1 mod p=(15<<27)+1
//! Precompute inverses for integer FFT, otherwise it will be very slow.
// Multiply two polynomials sum_i a[i]x^i and sum_i b[i]x^i
vector<ld> convolution(vector<ld> a, vector<ld> b) {
  int sz = a.size()+b.size()-1;
  int n  = 1<<int(ceil(log2(sz)));
  vector<Complex> av(n,0), bv(n,0), cv;
  for (int i=0; i<a.size(); i++) av[i] = a[i];
  for (int i=0; i<b.size(); i++) bv[i] = b[i];
  cv = FFT(bv); bv = FFT(av);
  for (int i=0; i<n; i++) av[i] = bv[i]*cv[i];
  cv = FFT(av, -1);
  // cv is now the convolution of a and b: cv[k] = sum_(i+j=k) a[i]*b[j]
  vector<ld> c(sz);
  for (int i=0; i<sz; i++)
    c[i] = cv[i].real(); // if result should be int, use int(cv[i].real()+0.5)
  return c;
}

const int N = 2e5+1;
vector<ld> a(N);

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  a[0] = 1;
  for(int i=0;i<n;i++) {
    int v;
    cin>>v;
    a[v] = 1;
  }
  vector<ld> b = convolution(a,a);
  int m;
  cin>>m;
  int ans = 0;
  for(int i=0;i<m;i++) {
    int v;
    cin>>v;
    if(b[v]>0.5) ans++;
  }
  cout<<ans<<nl;

  return 0;
}
