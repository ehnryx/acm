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

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y) and x = a^{-1}
// Returns gcd(a,b)
ll egcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  } else {
    ll d = egcd(b, a%b, y, x);
    y -= x * (a/b);
    return d;
  }
}
//*/

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
struct Int {
  ll x;
  Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
  operator ll() { return x; }
  Int operator + (const Int& n) const { return Int(x + n.x); }
  Int operator - (const Int& n) const { return Int(x - n.x); }
  Int operator * (const Int& n) const { return Int(x * n.x); }
  Int operator / (const Int& n) const { return Int(x * n.inv()); }
  void operator += (const Int& n) { x = (x + n.x) % MOD; }
  void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
  void operator *= (const Int& n) { x = (x * n.x) % MOD; }
  void operator /= (const Int& n) { x = (x * n.inv()) % MOD; }
  ll inv() const {
    if (x == 0) throw runtime_error("divide by zero");
    ll c, d;
    egcd(x, MOD, c, d);
    return (c < 0) ? c+MOD : c;
  }
};
//*/

/**
 * USAGE:
 *  to declare an nxn diagonal matrix: Matrix<T> mat(n,n,d);
 *  to declare a rxc matrix: Matrix<T> mat(r,c);
 *  can convert vector<vector<T>> to Matrix<T> implicitly;
 *
 *  to solve a system of equations: Ax = b
 *  define Matrix<T> A;
 *  then x = A.solve(b) where x and b are vectors
 *  free variables are all arbitrarily set to 0
 *  returns an empty vector if no solution
 */
template <class T> struct Matrix {
  int rows, cols;
  vector<vector<T>> a;
  Matrix(int r, int c, int v=0) {
    rows = r; cols = c;
    a.resize(r, vector<T>(c));
    if (v) for (int i = 0; i < min(r,c); i++)
      a[i][i] = v;
  }
  Matrix(const vector<vector<T>>& v) {
    rows = v.size(); cols = v[0].size();
    a = v;
  }
  vector<T>& operator [] (unsigned int i) {
    return a[i];
  }
  Matrix<T>& operator *= (const Matrix<T>& other) {
    return *this = *this * other;
  }
  Matrix<T> operator * (const Matrix<T>& other) {
    Matrix<T> res(rows,cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        res[i][j] = 0;
        for (int k = 0; k < cols; k++)
          res[i][j] += a[i][k] * other.a[k][j];
      }
    }
    return res;
  }
  vector<T> operator * (const vector<T>& v) {
    vector<T> res(rows);
    for (int i = 0; i < rows; i++) {
      res[i] = 0;
      for (int j = 0; j < cols; j++)
        res[i] += a[i][j] * v[j];
    }
    return res;
  }
  Matrix<T>& operator += (const Matrix<T>& other) {
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        a[i][j] += other.a[i][j];
    return *this;
  }
  vector<T> solve(vector<T> goal, int& x) {
    vector<int> piv, first; // pivot and first
    vector<T> res; // the solution
    Matrix<T> rdu(rows, cols); // reduced matrix
    for (int i = 0; i < rows; i++) {
      first.push_back(cols);
      for (int j = 0; j < cols; j++) {
        rdu[i][j] = a[i][j];
        if (a[i][j] != 0 && first[i] == cols)
          first[i] = j;
      }
    }
    for (int i = 0; i < rows; i++) {
      piv.push_back(0);
      for (int j = 0; j < rows; j++) {
        if (i == 0 || first[piv[i-1]] < first[j]) {
          piv[i] = j;
          break;
        }
      }
      for (int j = piv[i]+1; j < rows; j++)
        if (i == 0 || first[piv[i-1]] < first[j])
          if (first[j] < first[piv[i]])
            piv[i] = j;
      if (first[piv[i]] == cols) {
        piv.pop_back();
        break;
      }
      for (int j = 0; j < rows; j++) {
        if (j != piv[i] && first[j] == first[piv[i]]) {
          bool zero = true;
          T factor = rdu[j][first[piv[i]]] / rdu[piv[i]][first[piv[i]]];
          goal[j] -= factor * goal[piv[i]];
          for (int k = first[piv[i]]; k < cols; k++) {
            rdu[j][k] -= factor * rdu[piv[i]][k];
            if (rdu[j][k] == 0)
              rdu[j][k] = 0;
            if (rdu[j][k] == 0 && zero)
              first[j]++;
            else if (rdu[j][k] != 0)
              zero = false;
          }
          if (zero && goal[j] != 0)
            return res;
        }
      }
    }
    res.resize(rows, 0);
    int pos = cols-1;
    while (piv.empty() == false) {
      int curr = piv.back();
      piv.pop_back();
      while (first[curr] < pos)
        pos--;
      res[pos] = goal[curr];
      for (int j = pos+1; j < cols; j++)
        res[pos] -= res[j] * rdu[curr][j];
      res[pos] /= rdu[curr][pos];
      x += 1;
      pos--;
    }
    return res;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int h, w;
  cin >> h >> w;

  vector<Int> goal(h,0);
  Matrix<Int> mat(h,w);
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      int a;
      cin >> a;
      mat[i][j] = Int(a);
    }
  }

  int x = 0;
  mat.solve(goal, x);
  cout << x << nl;

  return 0;
}
