#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;




int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  ll n, k;
  cin >> n >> k;

  int ans = INF;
  for (int i=1; i<k; i++) {
    int cnt = 1;
    for (ll b = i; n-b > k-i; cnt++) {
      b = b + min(b, (n-b)/2);
    }
    ans = min(ans, cnt);
  }
  cout << ans << nl;

  return 0;
}
