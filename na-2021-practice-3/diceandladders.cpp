#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Matrix = vector<vector<ld>>;

void multiply(const Matrix& a, const Matrix& b, Matrix& c) {
  int n = size(a);
  c.resize(n, vector<ld>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      c[i][j] = 0;
      for(int k=0; k<n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}

vector<ld> multiply(const Matrix& a, const vector<ld>& b) {
  int n = size(a);
  vector<ld> res(n);
  for(int i=0; i<n; i++) {
    res[i] = 0;
    for(int k=0; k<n; k++) {
      res[i] += a[i][k] * b[k];
    }
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m, k;
  cin >> n >> m >> k;
  n *= m; // why does m even exist??

  ld goal;
  cin >> goal;

  vector<int> to(n + 1);
  for(int i=0; i<k; i++) {
    int a, b;
    cin >> a >> b;
    to[a] = b;
  }

  vector mat(n + 1, vector<ld>(n + 1));
  for(int i=1; i<=n; i++) {
    for(int d=1; d<=6; d++) {
      if(i + d >= n) {
        mat[n][i] += (ld)1 / 6;
      } else if(to[i+d]) {
        mat[to[i+d]][i] += (ld)1 / 6;
      } else {
        mat[i+d][i] += (ld)1 / 6;
      }
    }
  }

  const int M = 61;
  vector<Matrix> emats(M);
  emats[0] = mat;
  for(int i=1; i<M; i++) {
    multiply(emats[i-1], emats[i-1], emats[i]);
  }

  function<ld(int)> solve = [&](ll v) {
    vector<ld> res(n + 1);
    res[1] = 1;
    for(int i=0; i<M; i++) {
      if(v >> i & 1) {
        res = multiply(emats[i], res);
      }
    }
    return res[n];
  };

  ll ub = 1;
  while(solve(ub) < goal) {
    ub *= 2;
  }

  cerr << "ub: " << ub << nl;

  ll l = 0;
  ll r = ub;
  while(l < r) {
    ll mid = (l + r) / 2;
    if(solve(mid) < goal) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  cout << r << nl;

  return 0;
}
