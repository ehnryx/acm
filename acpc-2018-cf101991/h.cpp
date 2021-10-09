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

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  freopen("hawawshi.in", "r", stdin);

  int T;
  cin>>T;
  while(T--) {
    ll n,x,A,B,a,b,p;
    cin>>n>>x>>A>>B>>a>>b>>p;
    ll ainv = power(a,p-2,p);
    //cerr<<"ainv "<<ainv<<nl;
    int s = sqrt(p);
    unordered_map<int,int> dist;
    dist[x] = 0;
    //cerr<<"set dist "<<x<<" -> "<<0<<nl;
    for(int i=1;i<=s+7;i++) {
      x = ((x-b)*ainv%p + p) % p;
      if(dist.count(x)) break;
      dist[x] = i;
      //cerr<<"set dist "<<x<<" -> "<<i<<nl;
    }

    int cnt = 0;
    int den = B-A+1;
    for(int t=A;t<=B;t++) {
      int v = t;
      //cerr<<"solve for "<<v<<nl;
      ll as = power(a,s,p);
      ll inv = power(a-1,p-2,p);
      for(int i=0;i<s+7;i++) {
        if(dist.count(v) && dist[v] + i*s < n) {
          //cerr<<"@ "<<v<<" after "<<i<<" steps; dist "<<dist[v]<<" + "<<i*s<<nl;
          cnt++;
          break;
        }
        if(a==1) v = (as*v + s*b) % p;
        else v = (as*v + (as-1)*inv%p * b) % p;
      }
    }
    //cerr<<"cnt: "<<cnt<<nl;
    int g = __gcd(cnt,den);
    cout<<cnt/g<<"/"<<den/g<<nl;
  }

  return 0;
}
