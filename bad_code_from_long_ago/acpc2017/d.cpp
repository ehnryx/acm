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

  int parity[2];
  int T;
  int n, a;
  cin >> T;
  while (T--) {
    parity[0] = parity[1] = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a;
      parity[a%2]++;
    }
    if (parity[0] && parity[1]) cout << "no" << endl;
    else cout << "yes" << endl;
  }

  return 0;
}
