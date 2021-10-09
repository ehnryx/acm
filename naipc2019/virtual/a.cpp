#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

ld prob(int n, int k, int d) {
  if (k-2 > n-d) return 0;
  ld ret = (ld)k*(k-1)/((ld)(n-k+1)*(n-k+2));
  for (int i=3; i<=k; i++) {
    ret *= (ld)(n-d-k+i)/(n-k+i);
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(17);

  int n, k;
  cin >> n >> k;

  ld x[n], y[n];
  for (int i=0; i<n; i++) {
    cin >> x[i] >> y[i];
  }

  ld p[n];
  for (int i=0; i<=n; i++) {
    p[i] = prob(n,k,i);
  }

  ld ans = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i==j) continue;
      int dist = (j-i+n)%n + 1;
      ans += (x[i]*y[j] - x[j]*y[i]) * p[dist];
      //cerr << "P(" << n << ',' << k << ',' << dist << ")" << nl;
      //cerr << "ADD " << i << " -> " << j << " w/ prob " << prob(n,k,dist) << nl;
    }
  }
  cout << abs(ans)/2 << nl;

  return 0;
}
