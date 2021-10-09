#include <bits/stdc++.h>
using namespace std;

#define debug

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, a, g;
  ll sum;
  int T;
  cin >> T;
  while (T--) {
    g = 0;
    sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a;
      if (g == 0) g = a;
      else g = __gcd(g, a);
      sum += a;
    }
    cout << sum << " " << g << endl;
  }

  return 0;
}
