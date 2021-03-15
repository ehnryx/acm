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

const int N = 8;
char grid[N][N], ans[N][N];
int dsu[N*N], deg[N][N];
stack<int> dsu_memo;

int idx(int i, int j) {
  return i*N + j;
}

int find(int i) {
  if(dsu[i] == -1) return i;
  return find(dsu[i]); // no compression
}

bool link(int i, int j) {
  i = find(i);
  j = find(j);
  if(i == j) return false;
  dsu[i] = j;
  dsu_memo.push(i);
  return true;
}

void unlink() {
  dsu[dsu_memo.top()] = -1;
  dsu_memo.pop();
}

bool valid(int n) {
  for(int i=0; i<=n; i++) {
    for(int j=0; j<=n; j++) {
      if(isdigit(grid[i][j]) && deg[i][j] != grid[i][j] - '0') {
        return false;
      }
    }
  }
  return true;
}

bool check(int i, int j, function<bool(int,int)> f=less<int>()) {
  return !isdigit(grid[i][j]) || f(deg[i][j], grid[i][j] - '0');
}

bool solve(int i, int j, int n) {
  if(i == 0) return valid(n);
  if(j == 0) return solve(i-1, n, n);

  if(check(i, j) && check(i-1, j-1) && link(idx(i, j), idx(i-1, j-1))) {
    ans[i][j] = '\\';
    deg[i][j]++;
    deg[i-1][j-1]++;
    if(check(i, j, equal_to<int>()) && solve(i, j-1, n)) return true;
    deg[i][j]--;
    deg[i-1][j-1]--;
    unlink();
  }

  if(check(i, j-1) && check(i-1, j) && link(idx(i, j-1), idx(i-1, j))) {
    ans[i][j] = '/';
    deg[i][j-1]++;
    deg[i-1][j]++;
    if(check(i, j, equal_to<int>()) && solve(i, j-1, n)) return true;
    deg[i][j-1]--;
    deg[i-1][j]--;
    unlink();
  }

  return false;
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

  int n;
  cin >> n;
  for(int i=0; i<=n; i++) {
    for(int j=0; j<=n; j++) {
      cin >> grid[i][j];
    }
  }

  memset(dsu, -1, sizeof dsu);
  assert(solve(n, n, n));

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cout << ans[i][j];
    }
    cout << nl;
  }

  return 0;
}
