#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int N = 404;

int n, k, W;
int bm;
int w[N][N], c[N][N];
ll dp[N][N];

ll solve(int x, int y) {
  if (!(bm & (1 << c[x][y]))) return INFLL;
  if (x == n-1 && y == n-1 && (bm & (1 << c[x][y]))) return w[x][y];
  if (dp[x][y] != -1) return dp[x][y];
  ll ans = INFLL;
  if (x < n-1 && (bm & (1 << c[x+1][y]))) {
    ans = min(ans, solve(x+1, y) + w[x][y]);
  }
  if (y < n-1 && (bm & (1 << c[x][y+1]))) {
    ans = min(ans, solve(x, y+1) + w[x][y]);
  }
  return dp[x][y] = ans;
}
void recover(int x, int y, vector<int>& sol) {
  assert(bm & (1 << c[x][y]));
  sol.push_back(x);
  sol.push_back(y);
  if (x == n-1 && y == n-1) {
    return;
  }
  if (x < n-1 && (bm & (1 << c[x+1][y]))) {
    if (solve(x+1, y) + w[x][y] == solve(x, y)) {
      return recover(x+1, y, sol);
    }
  }
  assert(y < n-1 && (bm & (1 << c[x][y+1])) && solve(x, y+1) + w[x][y] == solve(x, y));
  recover(x, y+1, sol);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> k >> W;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> w[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> c[i][j]; c[i][j]--;
    }
  }
  int best = INF, bestbm; vector<int> besti;
  for (bm = 0; bm < (1 << k); bm++) {
    memset(dp, -1, sizeof dp);
    if (solve(0, 0) <= W && __builtin_popcount(bm) < best) {
      best = __builtin_popcount(bm);
      bestbm = bm;
      besti.clear();
      recover(0, 0, besti);
    }
  }
  if (best == INF) {
    puts("-1");
    return 0;
  }
  assert(besti.size() == 2*(2*n-1));
  cout << best << nl;
  for (int i : besti) {
    cout << i+1 << " ";
  }
  cout << nl;
  //assert(accumulate(seen.begin(), seen.end(), 0) == best);

  return 0;
}
