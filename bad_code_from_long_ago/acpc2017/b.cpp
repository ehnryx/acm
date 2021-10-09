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

  int a, b;
  int T;
  cin >> T;
  while (T--) {
    cin >> a >> b;
    if (a >= b) cout << "FunkyMonkeys" << endl;
    else cout << "WeWillEatYou" << endl;
  }

  return 0;
}
