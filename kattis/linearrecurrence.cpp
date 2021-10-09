#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Matrix {
  vector<vector<ll>> a;
  Matrix(int n=0) {
    a.resize(n, vector<ll>(n));
  }
  vector<ll>& operator [] (int i) {
    return a[i];
  }

  Matrix mul(const Matrix& o, ll m) const {
    int n = a.size();
    Matrix res = Matrix(n);
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        for(int k=0; k<n; k++) {
          res[i][j] += a[i][k] * o.a[k][j] % m;
        }
        res[i][j] %= m;
      }
    }
    return res;
  }

  vector<ll> mul(const vector<ll>& o, ll m) const {
    int n = a.size();
    vector<ll> res(n);
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        res[i] += a[i][j] * o[j] % m;
      }
      res[i] %= m;
    }
    return res;
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  Matrix mat(n+1);
  vector<ll> x(n+1);

  cin >> mat[0][n];
  for(int i=0; i<n; i++) {
    cin >> mat[0][i];
  }
  for(int i=1; i<n; i++) {
    mat[i][i-1] = 1;
  }
  mat[n][n] = 1;

  x[n] = 1;
  for(int i=0; i<n; i++) {
    cin >> x[n-1-i];
  }

  int q;
  cin >> q;
  while(q--) {
    ll t, m;
    cin >> t >> m;

    if(t < n) {
      cout << x[n-1-t] % m << nl;
      continue;
    }

    Matrix res(n+1);
    Matrix mul = mat;
    for(int i=0; i<=n; i++) {
      res[i][i] = 1;
    }
    for(t-=n-1; t>0; t/=2) {
      if(t&1) res = res.mul(mul, m);
      mul = mul.mul(mul, m);
    }
    cout << res.mul(x, m)[0] << nl;
  }

  return 0;
}
