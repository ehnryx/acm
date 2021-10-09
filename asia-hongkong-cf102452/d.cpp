#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
#define nl '\n'



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    ll k, n;
    cin >> k >> n;
    ll g = k;
    int len = 1;
    while(g < n) {
      n -= g;
      g *= k;
      len++;
    }
    g /= k;
    --n;
    for(int i=0; i<len; i++) {
      if(g == 0) for(;;);
      cout << (char)(10-k + n/g + '0');
      n -= (n/g) * g;
      g /= k;
    }
    cout<<nl;
  }

  return 0;
}
