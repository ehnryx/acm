//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 1e4 + 1;
int cnt[M];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, p;
  cin >> n >> p;
  string s;
  cin >> s;

  if(p == 2) {
    ll ans = 0;
    for(int i=0; i<n; i++) {
      if((s[i]-'0') % 2 == 0) {
        ans += i+1;
      }
    }
    cout << ans << nl;
  }

  else if(p == 5) {
    ll ans = 0;
    for(int i=0; i<n; i++) {
      if((s[i]-'0') % 5 == 0) {
        ans += i+1;
      }
    }
    cout << ans << nl;
  }

  else {
    reverse(s.begin(), s.end());

    ll cur = 0;
    ll mp = 1;
    cnt[0] = 1;
    for(char c : s) {
      cur = (cur + (c-'0') * mp) % p;
      mp = mp * 10 % p;
      cnt[cur]++;
    }

    ll ans = 0;
    for(int i=0; i<p; i++) {
      ans += (ll) cnt[i] * (cnt[i]-1) / 2;
    }
    cout << ans << nl;
  }

  return 0;
}
