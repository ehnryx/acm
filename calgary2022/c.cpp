#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const ld PI = acos((ld)-1);
const ld tier1 = (ld)1/PI;
const ld tier2 = (ld)1/PI/PI;
const ld tier3 = (ld)1/PI/PI/PI;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m, q;
  cin >> n >> m >> q;
  vector g(n+1, vector<char>(m+1, '.'));
  vector<tuple<int, int, char>> ev;
  for(int i=0; i<q; i++) {
    int a, b; char c;
    cin >> a >> b >> c;
    swap(a, b);
    g[a][b] = c;
    ev.emplace_back(a, b, c);
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] != '.') continue;
      ld cur = 0;
      for(auto [a, b, c] : ev) {
        int sgn = (c == '+' ? 1 : -1);
        cur += sgn / sqrt((ld)(i-a)*(i-a) + (ld)(j-b)*(j-b));
      }
      if(cur > tier1) g[i][j] = '0';
      else if(cur > tier2) g[i][j] = 'O';
      else if(cur > tier3) g[i][j] = 'o';
      else if(-cur > tier1) g[i][j] = '%';
      else if(-cur > tier2) g[i][j] = 'X';
      else if(-cur > tier3) g[i][j] = 'x';
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cout << g[i][j];
    }
    cout << nl;
  }

  return 0;
}
