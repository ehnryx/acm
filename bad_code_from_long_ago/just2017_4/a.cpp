/////////
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

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

  int n, last;
  int arr[100001];
  ll ans;

  int T; 
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i < n; i++) 
      cin >> arr[i];
    arr[n] = 0;

    ans = 0;
    for (int bit = 1; bit < 1e6; bit = bit<<1) {
      last = -1;
      for (int i = 0; i <= n; i++) {
        if ((bit & arr[i]) == 0) {
          ans += 1LL * (i-last)*(i-last-1)/2 * bit;
          last = i;
        }
      }
    }
    cout << ans << nl;
  }

  return 0;
}
