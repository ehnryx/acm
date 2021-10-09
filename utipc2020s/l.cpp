#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n; ll m;
  cin >> n >> m;
  ll g = 0;
  for(int i=0; i<n; i++) {
    ll a;
    cin >> a;
    g = __gcd(g, a - 1);
  }
  while(g%2 == 0) {
    g /= 2;
  }
  cerr<<"g = "<<g<<nl;

  function<ll(ll)> count = [=](ll d) {
    ll res = 0;
    for(int k=0; k<60; k++) {
      ll l = 0;
      ll r = m;
      while(l < r) {
        ll x = (l+r+1) / 2;
        if(x + ((__int128)d<<k) <= m) {
          l = x;
        } else {
          r = x-1;
        }
      }
      res += r;
    }
    return res;
  };

  ll ans = 0;
  for(ll d=1; d*d<=g; d++) {
    if(g%d) continue;
    ans += count(d);
    if(d*d != g) {
      ans += count(g/d);
    }
  }
  cout << ans << nl;

  return 0;
}
