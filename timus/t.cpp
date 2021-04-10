#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool nz(ld x) { return abs(x) > EPS; }

template <class T> struct Matrix {
  int n, m; valarray<T> a;
  Matrix(int _n=0, int _m=0): n(_n), m(_m) { a.resize(n*m); }
  T& operator () (int i, int j) { return a[i*m+j]; }
  valarray<T> row(int i) const { return a[slice(i*m, m, 1)]; }
  valarray<T> col(int j) const { return a[slice(j, n, m)]; }
  Matrix operator * (const Matrix& o) const { Matrix<T> s(n, o.m);
    for(int i=0; i<n; i++) for(int j=0; j<o.m; j++) {
      s(i, j) = (row(i) * o.col(j)).sum(); } return s; }
  void piv(int i, int j) {
    auto ri=row(i); a[slice(i*m,m,1)]=row(j); a[slice(j*m,m,1)]=ri; }
  valarray<T> solve(vector<T> b) { // destroys the matrix
    vector<int> v; for(int j=0, r=0; j<m; j++) { auto c = col(j);
      auto w = max_element(begin(c)+r, end(c), [](T& s, T& t) {
        return abs(s) < abs(t); }); int t = w-begin(c);
      if(nz(*w)) { piv(r,t); swap(b[r],b[t]); v.push_back(j);
        for(int i=r+1; i<n; i++) { T f = a[i*m+j] / a[r*m+j];
          a[slice(i*m,m,1)] -= row(r) * f; b[i] -= b[r] * f; } r++; } }
    int r=v.size(); for(int i=r; i<n; i++) if(nz(b[i])) return {};
    valarray<T> s(m); for(int i=r-1; i>=0; i--) {
      s[i] = (b[i] - (s*row(i)).sum()) / a[i*m+v[i]]; } return s; }
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  Matrix<ld> a(3, 3);
  a(0, 0) = 1;
  a(1, 1) = 1;
  a(2, 2) = 1;
  a(0, 1) = 1;
  a(0, 2) = 1;

/*
  Matrix<ld> out = a * a;
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      cout << out(i,j) << " ";
    }
    cout << nl;
  }
*/

  vector<ld> b = { 1, 0, 2 };
  auto r = a.solve(b);
  for(int it : r) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
