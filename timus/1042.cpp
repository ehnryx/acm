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
  friend int abs(const Int& v) { return v.n; }
  friend int nz(const Int& v) { return v.n; }
};
istream& operator >> (istream& is, Int& v) { return is >> v.n; }
ostream& operator << (ostream& os, const Int& v) { return os << v.n; }

template <class T> struct Matrix {
  int n, m; vector<vector<T>> a; Matrix() = default;
  Matrix(int d, int e): n(d), m(e) { a.resize(n, vector<T>(m)); }
  vector<T>& operator [] (int i) { return a[i]; }
  vector<T> solve(vector<T> b) {
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
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  Matrix<Int> a(n, n);
  for(int i=0; i<n; i++) {
    for(int v; cin >> v && v != -1; ) {
      a[v-1][i] = 1;
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
