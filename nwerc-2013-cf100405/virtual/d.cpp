#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int k, N;
int ans;
int l[9], h[9];
vector<int> grid[9];

inline bool check(int x, int y, int i) {
  return h[y] - x <= N - i;
}

void dfs(int x, int y) {
  //cerr << x << " " << y << " " << l[x] << endl;
  if (x > k) {
    ans++;
    /*
    for (int i = 0; i < k; i++) {
      for (int j : grid[i]) cout << j << " ";
      cout << endl;
    }
    cout << endl;
    */
    return;
  }
  int i = max(1, max(grid[x-1][y]+1, grid[x][y-1]));
  int nx = x, ny = y+1;
  if (ny > l[x]) {
    ny = 1;
    nx++;
  }
  for (; i <= N; i++) {
    if (check(x, y, i)) {
      grid[x][y] = i;
      dfs(nx, ny);
    } else return;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  while (cin >> k) {
    memset(h, 0, sizeof h);
    for (int i = 1; i <= k; i++) {
      cin >> l[i];
      for (int j = 0; j <= l[i]; j++) {
        h[j] = i;
      }
    }
    grid[0] = vector<int>(l[1]+1);
    for (int i = 1; i <= k; i++) {
      grid[i] = vector<int>(l[i]+1);
    }
    cin >> N;
    ans = 0;
    dfs(1, 1);
    cout << ans << nl;
  }

  return 0;
}
