#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';

#define FNAME "alter"

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, m;
  cin >> n >> m;
  cout << (n/2 + m/2) << nl;
  for(int i=1; i<=n/2; i++) {
    cout << 2*i << " " << 1 << " " << 2*i << " " << m << nl;
  }
  for(int i=1; i<=m/2; i++) {
    cout << 1 << " " << 2*i << " " << n << " " << 2*i << nl;
  }

  return 0;
}
