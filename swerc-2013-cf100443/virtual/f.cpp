#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

#define nl '\n'

ll odd[999][9], even[999][9];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int j=1; j<=5; j++) {
    odd[0][j] = 0;
    even[0][j] = j;
  }
  for (int i=1; i<999; i++) {
    odd[i][1] = odd[i-1][5];
    even[i][1] = even[i-1][5];
    for (int j=2; j<=5; j++) {
      if (i%2 == 0) {
        odd[i][j] = j * odd[i][1];
        even[i][j] = j * even[i][1];
      } else {
        odd[i][j] = even[i][j] = 0;
        for (int k=0; k<j; k++) {
          if (k%2 == 0) {
            odd[i][j] += odd[i][1];
            even[i][j] += even[i][1];
          } else {
            odd[i][j] += even[i][1];
            even[i][j] += odd[i][1];
          }
        }
      }
    }
  }

  for (;;) {
    ll n;
    cin >> n;
    if (n == -1) break;
    ++n;

    ll ans = 0;
    bool flip = false;
    //cerr << "SOLVE " << n-1 << nl;
    while (n > 0) {
      int i = 0;
      ll j = 1;
      while (j <= n) {
        i++;
        j *= 5;
      }
      --i;
      j /= 5;
      int k = n/j;
      ans += (flip ? odd[i][k] : even[i][k]);
      //cerr << "add " << i << " " << k << " " << flip << " -> " << (flip ? odd[i][k] : even[i][k]) << nl;
      flip ^= (i%2 == 1 && k%2 == 1);
      n -= k*j;
    }
    cout << ans << nl;
  }

  return 0;
}
