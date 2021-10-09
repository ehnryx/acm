#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 55;

ll fac[N];
void pre(int q) {
  fac[0] = 1;
  for (int i = 1; i < N; i++) {
    fac[i] = fac[i-1] * i % q;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    cout << "Case #" << tt << ": ";
    int n, k, q;
    cin >> n >> k >> q;
    pre(q);
    if (k >= n) {
      cout << fac[n] << nl;
    } else {
      cout << fac[k] * (1 + k * (n - k) + (n - k - 1) + (n - k) * (n - k - 1) - (n - k - 1)) % q << nl;
    }
  }

  return 0;
}
