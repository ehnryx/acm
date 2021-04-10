#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

const int MOD = 10007;
int inv[MOD];
struct Int {
  int n;
  Int(int _n=0): n(_n % MOD) { if(n<0) n += MOD; }
  Int operator * (const Int& o) const { return Int(n*o.n); }
  Int operator / (const Int& o) const { return Int(n*o.inverse()); }
  Int operator + (const Int& o) const { return Int(n+o.n); }
  Int operator - (const Int& o) const { return Int(n-o.n); }
  void operator += (const Int& o) { *this = *this + o; }
  void operator -= (const Int& o) { *this = *this - o; }
  friend int abs(const Int& v) { return v.n; }
  friend int nz(const Int& v) { return v.n; }
  int inverse() const {
    if(!inv[n]) {
      inv[n] = 1;
      for(int e=MOD-2, b=n; e; e/=2) {
        if(e&1) inv[n] = inv[n] * b % MOD;
        b = b*b % MOD;
      }
    }
    return inv[n];
  }
};
istream& operator >> (istream& is, Int& v) { return is >> v.n; }
ostream& operator << (ostream& os, const Int& v) { return os << v.n; }

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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  Matrix<Int> mat(n, n);
  for(int i=0; i<n; i++) {
    for(int j=0; j<5; j++) {
      int a;
      cin >> a;
      mat(i, a-1) = 1;
    }
  }

  Matrix<Int> a(n, n);
  vector<Int> b(n);
  for(int i=0; i<n; i++) {
    cin >> b[i];
    a(i, i) = 1;
  }

  for(--m; m; m/=2) {
    if(m&1) a = a * mat;
    mat = mat * mat;
  }
  auto sol = a.solve(b);
  for(int i=0; i<n; i++) {
    cout << sol[i] << " ";
  }
  cout << nl;

  return 0;
}
