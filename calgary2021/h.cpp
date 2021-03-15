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

const int N = 12, n = 10;
char region[N][N];
char grid[N][N];
int regcnt[N], rowcnt[N], colcnt[N];

bool valid_grid() {
  bool ok = true;
  for(int i=1; i<=n; i++) {
    ok &= (colcnt[i] == 2);
    ok &= (regcnt[i-1] == 2);
  }
  return ok;
}

bool solve(int i, int j) {
  if(i == 0) return valid_grid();
  if(j == 0) return rowcnt[i] == 2 && solve(i-1, n);

  int r = region[i][j] - '0';
  int cell = 0;
  for(int di=-1; di<=1; di++) {
    for(int dj=-1; dj<=1; dj++) {
      cell += (grid[i+di][j+dj] == '*');
    }
  }

  if(cell < 1 && rowcnt[i] < 2 && colcnt[j] < 2 && regcnt[r] < 2) {
    grid[i][j] = '*';
    rowcnt[i]++;
    colcnt[j]++;
    regcnt[r]++;
    if(solve(i, j-1)) return true;
    rowcnt[i]--;
    colcnt[j]--;
    regcnt[r]--;
  }

  grid[i][j] = '.';
  return solve(i, j-1);
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

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> region[i][j];
    }
  }
  solve(n, n);

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cout << grid[i][j];
    }
    cout << nl;
  }

  return 0;
}
