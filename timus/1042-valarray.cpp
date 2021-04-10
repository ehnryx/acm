#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

struct Int {
  bool n;
  Int(bool _n=0): n(_n) {}
  Int operator * (const Int& o) const { return Int(n&o.n); }
  Int operator / (const Int& o) const { return Int(n&o.n); }
  Int operator + (const Int& o) const { return Int(n^o.n); }
  Int operator - (const Int& o) const { return Int(n^o.n); }
  void operator += (const Int& o) { n ^= o.n; }
  void operator -= (const Int& o) { n ^= o.n; }
  friend int abs(const Int& v) { return v.n; }
  friend int nz(const Int& v) { return v.n; }
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

  int n;
  cin >> n;
  Matrix<Int> a(n, n);
  for(int i=0; i<n; i++) {
    for(int v; cin >> v && v != -1; ) {
      a(v-1, i) = 1;
    }
  }

  vector<Int> b(n, 1);
  static const int T = 50; for(int i=0; i<T; i++) { auto cpy = a; cpy.solve(b); }
  auto sol = a.solve(b);
  if(sol.size() == 0) {
    cout << "No solution" << nl;
  } else {
    for(int i=0; i<n; i++) {
      if(sol[i].n) {
        cout << i+1 << " ";
      }
    }
    cout << nl;
  }

  return 0;
}
