#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

const int N = 1e6+1;
int dsu[N];
int find(int i) {
  if(dsu[i]==-1) return i;
  return dsu[i] = find(dsu[i]);
}
bool link(int i, int j) {
  if(find(i)==find(j)) return false;
  dsu[find(i)] = find(j);
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  vector<int> primes;
  vector<bool> np(N);
  for(int i=2;i<1e3;i++) {
    if(!np[i]) {
      for(int j=i*i;j<N;j+=i) {
        np[j] = true;
      }
    }
  }
  for(int i=2;i<N;i++) {
    if(!np[i]) primes.push_back(i);
  }

  int T;
  cin>>T;
  for(int tt=1;tt<=T;tt++) {
    cout<<"Case #"<<tt<<": ";
    ll a,b,p;
    cin>>a>>b>>p;
    int ans = b-a+1;
    memset(dsu,-1,sizeof dsu);
    for(int i:primes) {
      if(i<p) continue;
      if(i>b-a) break;
      for(ll j = (b/i)*i;j-i>=a;j-=i) {
        ans -= link(j-a,j-i-a);
      }
    }
    cout<<ans<<nl;
  }

  return 0;
}
