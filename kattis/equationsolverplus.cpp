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

pair<vector<ld>,vector<bool>> solve(vector<vector<ld>> a, bool verbose=false) {
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
  for(int i=0; i<r; i++) {
    for(int k=0; k<i; k++) {
      ld f = a[k][pivot[i]] / a[i][pivot[i]];
      for(int j=pivot[i]; j<=m; j++) {
        a[k][j] -= a[i][j] * f;
      }
    }
  }

  if(verbose) {
    for(int i=0; i<n; i++) {
      for(int j=0; j<=m; j++) {
        if(j == m) cerr << "| ";
        cerr << a[i][j] << " ";
      }
      cerr << nl;
    }
  }

  for(int i=r; i<n; i++) {
    if(!is_zero(a[i][m])) {
      return {{}, {}};
    }
  }

  vector<ld> res(m);
  vector<bool> free(m, true);
  for(int i=r-1; i>=0; i--) {
    bool single = true;
    res[pivot[i]] = a[i][m];
    for(int j=pivot[i]+1; j<m; j++) {
      res[pivot[i]] -= res[j] * a[i][j];
      single &= is_zero(a[i][j]);
    }
    res[pivot[i]] /= a[i][pivot[i]];
    if(single) {
      free[pivot[i]] = false;
    }
  }
  return pair(res, free);
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
    auto [x, free] = solve(a);
    if(x.empty()) {
      cout << "inconsistent" << nl;
    } else {
      for(int i=0; i<n; i++) {
        if(free[i]) {
          cout << "? ";
        } else {
          cout << x[i] << " ";
        }
      }
      cout << nl;
    }
  }

  return 0;
}
