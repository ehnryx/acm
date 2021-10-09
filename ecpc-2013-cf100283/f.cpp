#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "army"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ll UB = 2.1e12;

ll sqr(ll x) { return x*x; }

ll sum(ll n) {
  //cerr << "SUM " << n << nl;
  ll r = floor(sqrt(n));
  //cerr << "  r " << r << nl;
  ll res = r*(r+1)*(2*r+1)/6;
  //cerr << "  base: " << res << nl;
  ll left = min(n-sqr(r),r);
  ll right = sqr(r+1)-n;
  //cerr << "  left: " << left << "  right: " << right << nl;
  res += left*(left+1)/2;
  if (n-sqr(r) > r) res += (r+1)*(r+2)/2 - right*(right+1)/2;
  //cerr << "  res: " << res << nl;
  //cerr << nl;
  return res;
}

void solve() {
  ll n;
  cin >> n;

  ll left = 1;
  ll right = UB;
  while (left<right) {
    ll mid = (left+right)/2;
    if (sum(mid) >= n) {
      right = mid;
    } else {
      left = mid+1;
    }
  }
  cout << left << nl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(TESTFILE ".in", "r", stdin);
#endif

  int T;
  cin >> T;

  for (int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";
    solve();
  }

  return 0;
}
