#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

namespace book {
  using vi = vector<int>;

  typedef ld T; // long double, Rational, double + mod<P>...
  typedef vector<T> vd; /// include-line
  typedef vector<vd> vvd; /// include-line

  const T eps = 1e-8, inf = 1/.0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

  struct LPSolver {
    int m, n;
    vi N, B;
    vvd D;

    LPSolver(const vvd& A, const vd& b, const vd& c) :
      m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, vd(n+2)) {
        for (int i=0; i<m; i++) for (int j=0; j<n; j++) D[i][j] = A[i][j];
        for (int i=0; i<m; i++) { B[i]=n+i; D[i][n]=-1; D[i][n+1] = b[i];}
        for (int j=0; j<n; j++) { N[j] = j; D[m][j] = -c[j]; }
        N[n] = -1; D[m+1][n] = 1;
      }

    void pivot(int r, int s) {
      T *a = D[r].data(), inv = 1 / a[s];
      for (int i=0; i<m+2; i++) if (i != r && abs(D[i][s]) > eps) {
        T *b = D[i].data(), inv2 = b[s] * inv;
        for (int j=0; j<n+2; j++) b[j] -= a[j] * inv2;
        b[s] = a[s] * inv2;
      }
      for (int j=0; j<n+2; j++) if (j != s) D[r][j] *= inv;
      for (int i=0; i<m+2; i++) if (i != r) D[i][s] *= -inv;
      D[r][s] = inv;
      swap(B[r], N[s]);
    }

    bool simplex(int phase) {
      int x = m + phase - 1;
      for (;;) {
        int s = -1;
        for (int j=0; j<=n; j++) if (N[j] != -phase) ltj(D[x]);
        if (D[x][s] >= -eps) return true;
        int r = -1;
        for (int i=0; i<m; i++) {
          if (D[i][s] <= eps) continue;
          if (r == -1 || MP(D[i][n+1] / D[i][s], B[i])
                       < MP(D[r][n+1] / D[r][s], B[r])) r = i;
        }
        if (r == -1) return false;
        pivot(r, s);
      }
    }

    T solve(vd &x) {
      int r = 0;
      for (int i=1; i<m; i++) if (D[i][n+1] < D[r][n+1]) r = i;
      if (D[r][n+1] < -eps) {
        pivot(r, n);
        if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
        for (int i=0; i<m; i++) if (B[i] == -1) {
          int s = 0;
          for (int j=1; j<=n; j++) ltj(D[i]);
          pivot(i, s);
        }
      }
      bool ok = simplex(1); x = vd(n);
      for (int i=0; i<m; i++) if (B[i] < n) x[B[i]] = D[i][n+1];
      return ok ? D[m][n+1] : inf;
    }
  };
}

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

  int T;
  cin >> T;
  while(T--) {
    ll a, b, c;
    cin >> a >> b >> c;
    /*
    book::vd x;
    book::T res = book::LPSolver(
        { {0, 2, 1, 3, 5},
          {2, 2, 0, 0, 0},
          {1, 0, 2, 1, 0} },
        {(ld)a, (ld)b, (ld)c},
        {1, 1, 1, 1, 1}).solve(x);
    cout << (ll)(res + 2 * book::eps) << nl;*/

    vector<tuple<int,int,int>> sad = {
      {0, 2, 1},
      {2, 2, 0},
      {1, 0, 2},
      {3, 0, 1},
      {5, 0, 0},
    };
    ll ans = 0;
    for(auto [x, y, z] : sad) {
      ll take = INFLL;
      if(x) take = min(take, a/x);
      if(y) take = min(take, b/y);
      if(z) take = min(take, c/z);
      a -= x*take;
      b -= y*take;
      c -= z*take;
      ans += take;
    }
    cout << ans << nl;
  }

  return 0;
}
