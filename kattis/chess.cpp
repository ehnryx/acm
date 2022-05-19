#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    char a, x;
    int b, y;
    cin >> a >> b >> x >> y;
    a -= 'A';
    x -= 'A';
    b -= 1;
    y -= 1;

    if ((a+x-b-y) % 2) {
      cout << "Impossible" << nl;
      continue;
    }

    if (a == x && b == y) {
      cout << "0 " << char(a + 'A') << " " << b + 1 << nl;
      continue;
    }

    if (abs(a-x) == abs(b-y)) {
      cout << "1 " << char(a + 'A') << " " << b + 1 << " "
        << char(x + 'A') << " " << y + 1 << nl;
      continue;
    }

    cout << "2 " << char(a + 'A') << " " << b + 1 << " ";
    int dxy = abs(abs(a - x) - abs(b - y)) / 2;
    if (abs(a-x) < abs(b-y)) {
      if (a < x) {
        if (a - dxy >= 0) {
          cout << char(a - dxy + 'A') << " " << (b + dxy * (y - b) / abs(y - b)) + 1 << " ";
        } else {
          cout << char(x + dxy + 'A') << " " << (y + dxy * (b - y) / abs(y - b)) + 1 << " ";
        }
      } else {
        if (x - dxy >= 0) {
          cout << char(x - dxy + 'A') << " " << (y + dxy * (b - y) / abs(y - b)) + 1 << " ";
        } else {
          cout << char(a + dxy + 'A') << " " << (b + dxy * (y - b) / abs(y - b)) + 1 << " ";
        }
      }
    } else {
      if (b < y) {
        if (b - dxy >= 0) {
          cout << char((a + dxy * (x - a) / abs(x - a)) + 'A') << " " << b - dxy + 1 << " ";
        } else {
          cout << char((x + dxy * (a - x) / abs(x - a)) + 'A') << " " << y + dxy + 1 << " ";
        }
      } else {
        if (y - dxy >= 0) {
          cout << char((x + dxy * (a - x) / abs(x - a)) + 'A') << " " << y - dxy + 1 << " ";
        } else {
          cout << char((a + dxy * (x - a) / abs(x - a)) + 'A') << " " << b + dxy + 1 << " ";
        }
      }
    }
    cout << char(x + 'A') << " " << y + 1 << nl;
  }

  return 0;
}
