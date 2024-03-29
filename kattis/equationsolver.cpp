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

bool is_zero(ld x) {
  return abs(x) < EPS;
}

vector<ld> solve(vector<vector<ld>> a) {
  int n = a.size();
  int m = (int)a[0].size() - 1;
  vector<int> pivot;
  for(int j=0, r=0; j<m; j++) {
    bool found = false;
    for(int i=r; i<n; i++) {
      if(is_zero(a[i][j])) continue;
      found = true;
      swap(a[i], a[r]);
      break;
    }
    if(found) {
      for(int i=r+1; i<n; i++) {
        ld f = a[i][j] / a[r][j];
        for(int k=j; k<=m; k++) {
          a[i][k] -= a[r][k] * f;
        }
      }
      pivot.push_back(j);
      r++;
    }
  }

  int r = pivot.size();
  for(int i=r; i<n; i++) {
    if(!is_zero(a[i][m])) {
      return {};
    }
  }

  vector<ld> res(m);
  vector<bool> free(m, true);
  for(int i=r-1; i>=0; i--) {
    free[pivot[i]] = false;
    res[i] = a[i][m];
    for(int j=pivot[i]+1; j<m; j++) {
      res[i] -= res[j] * a[i][j];
    }
    res[i] /= a[i][pivot[i]];
  }

  for(int i=0; i<m; i++) {
    if(free[i]) {
      res[i] = NAN;
    }
  }
  return res;
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

  for(int n; cin >> n && n; ) {
    vector a(n, vector<ld>(n+1));
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        cin >> a[i][j];
      }
    }
    for(int i=0; i<n; i++) {
      cin >> a[i][n];
    }
    vector<ld> x = solve(a);
    if(x.empty()) {
      cout << "inconsistent" << nl;
    } else {
      bool ok = true;
      for(int i=0; i<n; i++) {
        ok &= !isnan(x[i]);
      }
      if(ok) {
        for(int i=0; i<n; i++) {
          cout << x[i] << " ";
        }
        cout << nl;
      } else {
        cout << "multiple" << nl;
      }
    }
  }

  return 0;
}
