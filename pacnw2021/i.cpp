#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 9;
char g[N][N];
char ans[N][N];

bool sum_valid(int x, int y, int n) {
  if(g[x][y] == '+') return true;
  bool unk = false;
  int want = g[x][y] - '0';
  if(x<n && y<n) {
    if(!ans[x][y]) unk = true;
    else if(ans[x][y] == '\\') want--;
  }
  if(x<n && y>0) {
    if(!ans[x][y-1]) unk = true;
    else if(ans[x][y-1] == '/') want--;
  }
  if(x>0 && y<n) {
    if(!ans[x-1][y]) unk = true;
    else if(ans[x-1][y] == '/') want--;
  }
  if(x>0 && y>0) {
    if(!ans[x-1][y-1]) unk = true;
    else if(ans[x-1][y-1] == '\\') want--;
  }
  if(unk) return want >= 0;
  else return want == 0;
}

vector<tuple<int, int>> memo;
int dsu[N*N], sz[N*N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return find(dsu[i]);
}
bool link(int x, int y, int a, int b) {
  int i = find(x*N + y);
  int j = find(a*N + b);
  if (i == j) return false;
  if (sz[i] < sz[j]) swap(i, j);
  memo.emplace_back(i, j);
  dsu[j] = i;
  sz[i] += sz[j] + 1;
  return true; // need to unlink
}
void unlink() {
  auto [i, j] = memo.back();
  memo.pop_back();
  sz[i] -= sz[j] + 1;
  dsu[j] = -1;
}

bool solve(int x, int y, int n) {
  if (x == n) {
    return true;
  }

  if (y == n) {
    return solve(x+1, 0, n);
  }

  // try forward /
  {
    ans[x][y] = '/';
    if(sum_valid(x, y, n) &&
        sum_valid(x+1, y, n) &&
        sum_valid(x, y+1, n) &&
        sum_valid(x+1, y+1, n) &&
        link(x, y+1, x+1, y)) {
      if (solve(x, y+1, n)) {
        return true;
      }
      unlink();
    }
    ans[x][y] = 0;
  }

  // try other
  {
    ans[x][y] = '\\';
    if(sum_valid(x, y, n) &&
        sum_valid(x+1, y, n) &&
        sum_valid(x, y+1, n) &&
        sum_valid(x+1, y+1, n) &&
        link(x, y, x+1, y+1)) {
      if (solve(x, y+1, n)) {
        return true;
      }
      unlink();
    }
    ans[x][y] = 0;
  }

  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=0; i<=n; i++) {
    for(int j=0; j<=n; j++) {
      cin >> g[i][j];
    }
  }

  memset(dsu, -1, sizeof dsu);
  assert(solve(0, 0, n));

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cout << ans[i][j];
    }
    cout << nl;
  }

  return 0;
}
