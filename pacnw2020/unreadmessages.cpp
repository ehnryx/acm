#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  map<int, int> last;

  ll ans = 0;
  for (int i = 1; i <= m; i++) {
    int sender;
    cin >> sender;
    ans += n - (i - last[sender]);
    last[sender] = i;
    cout << ans << nl;
  }

  return 0;
}
