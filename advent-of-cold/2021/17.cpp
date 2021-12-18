#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

#define int ll
  int a, b, x, y;
  cin >> a >> x >> b >> y;

  set<pair<int, int>> ans;
  for(int i=1; i<=x; i++) {
    int mx = 0;
    for(int j=67; j>=-68; j--) {
      int dy = j;
      int dx = i;
      int Y = 0;
      int X = 0;
      while(Y >= b) {
        Y += dy;
        X += dx;
        dx = max (0LL, dx-1);
        dy -= 1;
        mx = max(mx, Y);
        if(a<=X && X<=x && b<=Y && Y<=y){
          cerr << a << " " << x << " " << b << " " << y << " -> " << X << " " << Y << nl;
          ans.insert(pair(i, j));
          break;
        }
      }
    }
  }
  cout << ans.size() << nl;

  return 0;
}
