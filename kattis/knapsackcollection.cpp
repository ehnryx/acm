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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n; ll s,t;
  cin>>n>>s>>t;
  ll a[n];
  for(int i=0;i<n;i++) {
    cin>>a[i];
  }
  sort(a,a+n);

  map<ll,ll> need;
  for(int i=0;i<n;i++) {
    if(need.count(a[i])) continue;
    multiset<ll> left;
    for(int j=0;j<n;j++) {
      left.insert(a[j]);
    }
    ll cur = a[i];
    ll res = 0;
    while(!left.empty()) {
      auto it = left.lower_bound(cur);
      if(it==left.end()) it = left.begin();
      res += (*it + s-cur) % s + t;
      cur = (*it + t) % s;
      left.erase(it);
    }
    need[a[i]] = res;
  }

  ll minv = INFLL;
  ll maxv = -1;
  ll sum = 0;
  for(auto it=need.begin();it!=need.end();it++) {
    ll pre;
    if(it==need.begin()) pre = need.rbegin()->first;
    else pre = prev(it)->first;
    ll x = (it->first + s - (pre+1)) % s + 1;
    sum += x*(x-1)/2 + x*it->second;
    minv = min(minv, it->second);
    maxv = max(maxv, it->second + x-1);
  }

  cout<<minv<<nl;
  cout<<maxv<<nl;
  ll g = __gcd(sum,s);
  cout<<sum/g<<"/"<<s/g<<nl;

  return 0;
}
