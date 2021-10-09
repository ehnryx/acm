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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll inverse(ll n) {
  if(__gcd(n,(ll)10001) != 1) return 0;
  ll res = 1;
  for(int e=9792-1;e;e/=2) {
    if(e&1) res = res*n % 10001;
    n = n*n % 10001;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  ll v[n];
  for(int i=0;i<n;i++) {
    cin>>v[i];
  }
  if(n==1) {
    cout<<v[0]<<nl;
    return 0;
  }

  const int m = 10001;
  for(ll i=0;i<m;i++) {
    if(inverse(i+1)*(i+1) % m != 1) continue;
    ll j = ((v[1] - i*i*v[0])%m * inverse(i+1) % m + m) % m;
    assert(v[1] == (i*i*v[0] + i*j + j) % m);
    bool ok = true;
    for(int s=2;s<n;s++) {
      if(v[s] != (i*i*v[s-1] + i*j + j) % m) {
        ok = false;
        break;
      }
    }
    if(ok) {
      for(int s=0;s<n;s++) {
        cout<<(i*v[s]+j)%m<<nl;
        if(s<n-1) assert(v[s+1] == (i*(i*v[s]+j)%m+j)%m);
      }
      return 0;
    }
  }

  return 0;
}
