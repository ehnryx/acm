//
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

  ll f[11];
  f[0] = 1;
  for (int i = 1; i <= 10; i++) {
    f[i] = f[i-1] * i;
  }

  ll ans;
  int n, odd;
  string s;
  int letters[26];

  int T;
  cin >> T;
  while (T--) {
    memset(letters, 0, sizeof(letters));
    cin >> n;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
      letters[s[i]-'a']++;
    odd = 0;
    for (int i = 0; i < 26; i++) {
      if (letters[i] % 2 == 1) {
        letters[i]--;
        odd++;
      }
    }
    if (odd > 1) {
      ans = 0;
    } else {
      ans = f[n/2];
      for (int i = 0; i < 26; i++) {
        ans /= f[letters[i]/2];
      }
    }
    cout << ans << nl;
  }

  return 0;
}
