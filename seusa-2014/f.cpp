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
const ll MOD = 1e9+9;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y), then x = a^{-1}
// Returns gcd(a,b)
//*!
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
//*!
struct Int {
    ll x;
    Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
    operator ll() { return x; }
    ll fix() {
      x %= MOD; if (x < 0) x += MOD;
      return x;
    }
    Int operator + (const Int& n) const { return Int(x + n.x); }
    Int operator - (const Int& n) const { return Int(x - n.x); }
    Int operator * (const Int& n) const { return Int(x * n.x); }
    Int operator / (const Int& n) const { return Int(x * n.inv()); }
    void operator += (const Int& n) { x += n.x; }
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

////////////////////////////////////////////////////////////////////////
// Matrix Struct (TESTED)
// TESTED ON:
//   Multiplication
//     kattis:tritiling, cf:222e
//   Row Reduction
//     kattis:primonimo, cf:100962a
//
// to declare an nxn diagonal matrix: Matrix<T> mat(n,n,d);
// to declare a rxc matrix: Matrix<T> mat(r,c);
// can construct a matrix with a vector<vector<T>>
//
// to solve a system of equations: Ax = b
// define Matrix<T> A;
// then x = A.solve(b, rank, pivot); (rank and pivot are optional)
// if no solution, x = empty vector
// free variables set to 0, and corresponding pivots set to -1
// EDIT the iszero function for non-integer T !!
//*!
template <class T> struct Matrix {
    int rows, cols;
    vector<vector<T>> a;

    // diagonal constructor
    Matrix(int r, int c, int v=0) {
        rows = r; cols = c;
        a.resize(r, vector<T>(c));
        if (v) for (int i = 0; i < min(r,c); i++)
            a[i][i] = v;
    }
    // 2d vector constructor
    Matrix(const vector<vector<T>>& v) {
        rows = v.size(); cols = v[0].size();
        a = v;
    }
    // access elements
    vector<T>& operator [] (unsigned int i) {
        return a[i];
    }

    // operations
    void operator *= (const Matrix<T>& other) {
        vector<vector<T>> res(rows, vector<T>(cols));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res[i][j] = 0;
                for (int k = 0; k < cols; k++)
                    res[i][j] += a[i][k] * other.a[k][j];
                res[i][j].fix();
            }
        }
        a = res;
    }
};
//*/

bool hit(int bm, int n, int j) {
  if (j>=2 && (bm&1<<(n+j-2))) return true;
  if (j+2<n && (bm&1<<(n+j+2))) return true;
  if (j>=1 && (bm&1<<(j-1))) return true;
  if (j+1<n && (bm&1<<(j+1))) return true;
  return false;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  Matrix<Int> mat(1<<2*n,1<<2*n,0);
  for (int bm=0; bm<1<<2*n; bm++) {
    int nxt = bm>>n;
    for (int i=0; i<1<<n; i++) {
      bool ok = true;
      for (int j=0; j<n; j++) {
        if ((i&1<<j) && hit(bm,n,j)) {
          ok = false;
          break;
        }
      }
      if (ok) {
        mat[nxt|i<<n][bm] = 1;
      }
    }
  }

  Matrix<Int> ans(1<<2*n,1<<2*n,1);
  for (int i=m; i>0; i/=2) {
    if (i&1) ans *= mat;
    mat *= mat;
  }

  Int res = 0;
  for (int i=0; i<1<<2*n; i++) {
    res += ans[i][0];
  }
  cout << res.fix() << nl;

  return 0;
}
