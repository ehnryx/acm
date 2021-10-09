#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const ll INF = 0x3f3f3f3f;

const int N = 1e5+1;
int d[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;

  while (T--) {
    int n;
    cin >> n;

    int len = 0;
    for (int i=1; i<n; i++) {
      cin >> d[i];
      len += d[i];
    }

    ll cur = 0;
    ll add = 0;
    ll sub = 0;
    for (int i=1; i<=n; i++) {
      if (i%2) {
        sub += d[(i+1)/2];
        cur += add;
      } else {
        sub += d[n-i/2];
        add += len;
        cur += add;
        len -= sub;
        sub = 0;
      }
      cout << cur;
      if (i<n) cout << ' ';
    }
    cout << nl;
  }

  return 0;
}
