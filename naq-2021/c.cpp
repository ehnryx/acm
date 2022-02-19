#include <bits/stdc++.h>
using namespace std;

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

  ll n;
  cin >> n;

  vector<bool> p(100000);

  string ans;
  ld best = 0;

  ll m = 1;
  for(int i=2; m <= n; i++){
    p[i] = true;
    for(int j=2; j<i; j++) {
      if(i%j==0){
        p[i]=false;
      }
    }

    ll t=m;
    for(int j=1; j<i; j++) {
      if(p[j]){
        assert(t % j == 0);
        t /= j;
        t *= j-1;
      }
    }

    if((ld)(m-t)/m > best){
      best=(ld)(m-t)/m;
      ll g = __gcd(t, m);
      ans = to_string((m-t)/g) + "/" + to_string(m/g);
    }

    if(p[i]) {
      if(m>n/i+2) break;
      m *= i;
    }
  }


  cout << ans << nl;

  return 0;
}
