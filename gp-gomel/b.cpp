#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pii = pair<int,int>;
using ll = long long;
const char nl = '\n';

const int INF = 0x3f3f3f3f;

int freq(ll m) {
  return __builtin_ctzll(m) + 1;
}

pair<ll,ll> count(ll n, ll m) {
  ll res = 0;
  for(ll f=1; f<m; f*=2) {
    ll t = (m-1)/f;
    ll add = t*(t+1)/2 * f;
    if(add <= n) {
      n -= add;
      res += t;
    } else {
      return make_pair(-2*INF, -2*INF);
    }
  }
  return make_pair(res, n);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    ll n;
    cin >> n;
    ll l = 1;
    ll r = 2e9;
    while(l<r) {
      ll m = (l+r)/2;
      ll rest = count(n, m).second;
      if(rest/m > freq(m)) {
        l = m+1;
      } else {
        r = m;
      }
    }
    ll have, rest;
    tie(have, rest) = count(n, r);
    assert(rest/r <= freq(r));
    cout << have + rest/r << nl;
  }

  return 0;
}
