#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power[19];
void init() {
  power[0] = 1;
  for (int i = 1; i <= 17; i++) {
    power[i] = power[i-1]*10;
  }
}

bool valid(ll x) {
  int len = 0;
  for (ll i = 1; i <= x; i *= 10) {
    len++;
  }

  int half = len/2;
  int left = x/power[half];
  int right = x%power[half];
  if (half == 0 || left == 0 || right == 0) return false;
  else return __gcd(x/power[half], x%power[half]) == 1;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  while (T--) {
    ll left, right;
    cin >> left >> right;

    bool found = false;
    for (ll i = right; i >= left; i--) {
      if (valid(i)) {
        cout << i << nl;
        found = true;
        break;
      }
    }

    if (!found) {
      cout << -1 << nl;
    }
  }

  return 0;
}
