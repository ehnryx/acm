#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

const int MOD = 10007;
int inv[MOD];
struct Int {
  int n;
  Int(int _n=0): n(_n<MOD ? _n : _n - MOD) {}
  Int operator * (const Int& o) const { return Int(n*o.n % MOD); }
  Int operator / (const Int& o) const { return Int(n*o.inverse() % MOD); }
  Int operator + (const Int& o) const { return Int(n+o.n); }
  Int operator - (const Int& o) const { return Int(n-o.n+MOD); }
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
  int n, m; vector<vector<T>> a; Matrix() = default;
  Matrix(int d, int e): n(d), m(e) { a.resize(n, vector<T>(m)); }
  vector<T>& operator [] (int i) { return a[i]; }
  vector<T> solve(vector<T> b) { // destroys the matrix
    vector<int> v; for(int j=0, r=0; j<m; j++) {
      int w = max_element(begin(a) + r, end(a), [=](auto& s, auto& t) {
        return abs(s[j]) < abs(t[j]); }) - begin(a);
      if(nz(a[w][j])) { swap(a[r],a[w]); swap(b[r],b[w]);
        for(int i=r+1; i<n; i++) { T f=a[i][j]/a[r][j];
          for(int k=j; k<m; k++) a[i][k] = a[i][k] - a[r][k] * f;
          b[i] = b[i] - b[r] * f; } v.push_back(j); r++;
      } } int r=v.size(); for(int i=r; i<n; i++) if(nz(b[i])) return {};
      vector<T> s(m); for(int i=r-1; i>=0; i--) {
        for(int j=v[i]+1; j<m; j++) b[i] = b[i] - a[i][j]*s[j];
        s[v[i]] = b[i] / a[i][v[i]]; } return s; }
  Matrix transpose() const { Matrix<T> r(m,n);
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) r[i][j] = a[j][i];
    return r; }
  Matrix operator * (const Matrix& o) const {
    Matrix<T> r(n,o.m), b = o.transpose();
    for(int i=0;i<n;i++) for(int j=0;j<o.m;j++) for(int k=0;k<m;k++) {
      r[i][j] = r[i][j] + a[i][k] * b[j][k]; } return r; }
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
      mat[i][a-1] = 1;
    }
  }

  Matrix<Int> a(n, n);
  vector<Int> b(n);
  for(int i=0; i<n; i++) {
    cin >> b[i];
    a[i][i] = 1;
  }

  vector<Matrix<Int>> twos;
  for(--m; m; m/=2) {
    if(m&1) twos.push_back(mat);
    mat = mat * mat;
  }
  for(auto& t : twos) {
    b = t.solve(b);
  }
  for(int i=0; i<n; i++) {
    cout << b[i] << " ";
  }
  cout << nl;

  return 0;
}
