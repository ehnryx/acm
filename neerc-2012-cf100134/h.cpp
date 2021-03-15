#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")

#include <bits/stdc++.h>

using namespace std;

#define FILENAME "hyperdrome"

#define nl '\n'
typedef long long ll;
typedef long double ld;

const int N = 300300;
const int K = 26*2;

int toi(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  }
  return c-'A' + 26;
}

unordered_map<ll, int> mp;
int n;
char s[N];
ll f[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  cin >> n;
  cin >> (s+1);
  for (int i=1; i<=n; ++i) {
    f[i] = f[i-1]^(1LL<<toi(s[i]));
    //mp[f[i]]++;
  }
  ll ans = 0;
  for (int i=n; i>=1; --i) {
    ll goal = f[i-1];
    mp[f[i]]++;
    ans += mp[goal];
    for (int k=0; k<K; ++k) {
      if(mp.count(goal^(1LL<<k))) {
        ans += mp[goal^(1LL<<k)];
      }
    }
  }
  /*
  for (int i=1; i<=n; ++i) {
    ll goal = f[i-1];
    ans += mp[goal];
    for (int k=0; k<K; ++k) {
      ans += mp[goal^(1LL<<k)];
    }
    mp[f[i]]--;
  }
  */
  cout << ans << "\n";

  return 0;
}
