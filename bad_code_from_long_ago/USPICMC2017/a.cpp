#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  bool yes = false;
  int lower, upper;
  int n, goal, temp;
  cin >> n >> goal;
  lower = INF;
  upper = -1;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    lower = min(lower, temp);
    upper = max(upper, temp);
    if (temp == goal)
      yes = true;
  }
  if (yes) cout << 1 << nl;
  else if (lower < goal && goal < upper) cout << 2 << nl;
  else cout << -1 << nl;

  return 0;
}
