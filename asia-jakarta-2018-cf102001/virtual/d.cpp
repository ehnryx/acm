#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n,m;
  cin >> n >> m;

  string g[n];
  for (int i=0; i<n; i++) {
    cin >> g[i];
  }

  if (n == 1 || m == 1) {
    int ans = 0;
    if (n==1 && m==1) {
    } else if (n==1) {
      for (int j=1; j<m-1; j++) {
        ans += (g[0][j] == '.');
      }
    } else {
      for (int i=1; i<n-1; i++) {
        ans += (g[i][0] == '.');
      }
    }
    cout << ans << nl;
    return 0;
  }

  if (n == 2 || m == 2) {
    int ans = 0;
    if (n == 2 && m == 2) {
    } else if (n == 2) {
      for (int j=1; j<m-1; j++) {
        ans += (g[0][j] == '.' && g[1][j] == '.');
      }
    } else {
      for (int i=1; i<n-1; i++) {
        ans += (g[i][0] == '.' && g[i][1] == '.');
      }
    }
    cout << ans << nl;
    return 0;
  }

  int ans = 0;
  for (int i=1; i<n-1; i++) {
    for (int j=1; j<m-1; j++) {
      ans += (g[i][j] == '.');
    }
  }
  bool good = false;
  for (int i=1; i<n-1; i++) {
    if (g[i][0] == '#' || g[i][m-1] == '#') {
      good = true;
    }
  }
  for (int j=1; j<m-1; j++) {
    if (g[0][j] == '#' || g[n-1][j] == '#') {
      good = true;
    }
  }
  cout << ans + !good << nl;

  return 0;
}
