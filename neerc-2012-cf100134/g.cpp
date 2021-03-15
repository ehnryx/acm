#include <bits/stdc++.h>

using namespace std;

#define FILENAME "great"

#define nl '\n'
typedef long long ll;
typedef long double ld;

ll count(ll n, int k) {
  if(n < 0) return 0;
  if(n < k) return n + 1;

  ll tot = 0;
  ll mul = 1;
  int e = 0;
  int last = 0;
  while(tot <= n && mul <= n) {
    if(e % 2 == 0) {
      if(tot + mul*(k-1) > n) break;
      tot += mul*(k-1);
      last = e;
    }
    mul *= k;
    e++;
  }
  mul = min(mul, n + 1);

  ll add = llround(powl(k, last/2 + 1));
  ll ans = 0;
  for(int d=0; d<k; d++) {
    if(tot + mul*d <= n) {
      ans += add;
    } else {
      ans += count(n - mul*d, k);
    }
  }
  return ans;
}

int main() {
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  ll n; int k;
  cin >> n >> k;
  cout << count(n, k) << nl;

  return 0;
}
