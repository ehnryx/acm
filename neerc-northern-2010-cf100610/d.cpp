#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
const char nl = '\n';

#define FILE "defense"

int main() {
  if (fopen(FILE ".in", "r")) {
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
  }

  int n, m, k;
  cin >> n >> m >> k;
  int x[k+2], y[k+2];
  for(int i=1; i<=k; i++) {
    cin >> x[i] >> y[i];
  }
  x[0] = y[0] = 0;
  x[k+1] = n+1;
  y[k+1] = m+1;
  sort(x, x+k+2);
  sort(y, y+k+2);

  int maxx = 0;
  int maxy = 0;
  for(int i=1; i<k+2; i++) {
    maxx = max(maxx, x[i]-x[i-1]);
    maxy = max(maxy, y[i]-y[i-1]);
  }
  assert(maxx>0 && maxy>0);
  cout << (ll)(maxx-1)*(maxy-1) << nl;

  return 0;
}
