#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 12;
char g[N][N];

void solve(int i, int j, multiset<string>& all, string& s) {
  all.erase(s);
  if(!g[i][j] || size(s) == 10) return;
  s.push_back(g[i][j]);
  g[i][j] = 0;
  for(auto [di, dj] : {
      pair(1, 0), pair(0, 1), pair(-1, 0), pair(0, -1) }) {
    solve(i + di, j + dj, all, s);
  }
  g[i][j] = s.back();
  s.pop_back();
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
    }
  }
  int w;
  cin >> w;
  multiset<string> all;
  for(int i=0; i<w; i++) {
    string s;
    cin >> s;
    all.insert(s);
  }

  string builder;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      solve(i, j, all, builder);
    }
  }

  cout << w - size(all) << nl;

  return 0;
}
