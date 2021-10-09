#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  ld ans = 0;
  int k, r;
  cin >> k >> r;
  for (int a = 1; a <= k; a++) {
    ld up = (ld)((1<<k) - (1<<a));
    ld down = (ld)((1<<k) - 1);
    ld temp = 1;
    for (int j = 0; j <= r-2; j++)
      temp *= (up-j)/(down-j);
    ans += temp;
  }
  cout << fixed << setprecision(5) << ans << nl;

  return 0;
}
