#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 1010;


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, m; cin >> n >> m;
  bitset<N> cur;
  int l; cin >> l;
  for (int i = 0; i < l; i++) {
    int x; cin >> x;
    cur[x-1] = 1;
  }
  vector<bitset<N>> a(n);
  for (int i = 0; i < n; i++) {
    int k; cin >> k;
    for (int j = 0; j < k; j++) {
      int y; cin >> y;
      a[i][y-1] = 1;
    }
  }
  for (int ans = 0; ans <= 3*n; ans++) {
    if (!cur.count()) {
      cout << ans << nl;
      return 0;
    }
    cur ^= a[ans%n];
  }
  cout << -1 << nl;

  return 0;
}
