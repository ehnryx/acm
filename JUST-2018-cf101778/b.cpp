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

bool valid(ll n, ll a, ll d) {
  ll high = 2*a*d + (d-1)*d/2;
  ll low = (n-d); 
  return high+low <= n*a;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    int n, a;
    cin >> n >> a;

    if (n <= 2*a-1) {
      cout << n << nl;
    }
    else {
      n -= 2*a-1;
      int left, right, mid;
      left = 0;
      right = n;
      while (left <= right) {
        mid = (left+right)/2;
        if (valid(n, a, mid)) {
          left = mid+1;
        } else {
          right = mid-1;
        }
      }
      if (!valid(n, a, mid)) mid--;
      cerr << "mid: " << mid << nl;
      cout << 2*a-1 + mid << nl;
    }
  }

  return 0;
}
