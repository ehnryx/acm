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
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ll P = 1789;
const ll M = 1e9+9;

const ll N = 2e6 + 1;
ll p[N];

ll power(ll n, int e, ll m) {
  ll r = 1;
  for( ; e>0; e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(string s; cin >> s; ) {
    if(s == ".") break;
    int n = s.size();
    for(int i=0; i<n; i++) {
      p[i+1] = (p[i] * P + s[i]) % M;
    }
    for(int len=1; len<=n; len++) {
      if(n % len != 0) continue;
      ll H = power(P, len, M);
      bool ok = true;
      for(int j=len; j<n && ok; j+=len) {
        ll cur = (p[j+len] + M - p[j] * H % M) % M;
        ll pre = (p[j] + M - p[j-len] * H % M) % M;
        ok &= (cur == pre);
      }
      if(ok) {
        cout << n/len << nl;
        break;
      }
    }
  }

  return 0;
}
