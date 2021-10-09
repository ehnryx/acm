#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 2 * 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ll N = 1e5;

ll add(ll a, ll b) {
  if(INFLL-a<b) return INFLL;
  return a+b;
}

ll mul(ll a, ll b) {
  if(!a||!b) return 0;
  if(INFLL/a<b) return INFLL;
  else return a*b;
}

ll sum(ll a, ll b) {
  return mul(b-a,b-a+1)/2 + mul(a,b-a+1);
}

ll ans;
ll solve(ll n, ll m, ll ub) {
  ans = 0;
  ll res = 0;
  for(int i=1;i<=min(n,N);i++) {
    ll j=min(m,ub/i);
    if(i<j) {
      ans += j-i;
      res = add(res,mul(i,sum(i+1,j)));
    }
  }
  for(int i=1;i<=min(m,N);i++) {
    ll j=min(n,ub/i);
    if(i<j) {
      ans += j-i;
      res = add(res,mul(i,sum(i+1,j)));
    }
  }
  for(int i=1;i<=min(min(m,n),N)&&(ll)i*i<=ub;i++) {
    ans++;
    res = add(res,(ll)i*i);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  ll n,m,k;
  cin>>n>>m>>k;
  ll l=0;
  ll r=1e12;
  while(l<r) {
    ll v=(l+r+1)/2;
    if(solve(n,m,v)<=k) {
      l=v;
    } else {
      r=v-1;
    }
  }
  cout<<ans+(k-solve(n,m,l))/(l+1)<<nl;

  return 0;
}
