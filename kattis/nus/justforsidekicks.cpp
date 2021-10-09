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

const int N = 2e5+1;
struct BIT {
  int f[N];
  BIT() { memset(f,0,sizeof f); }
  void insert(int x, int v) {
    for(;x<N;x+=x&-x) {
      f[x] += v;
    }
  }
  int query(int x) {
    int res = 0;
    for(;x>0;x-=x&-x) {
      res += f[x];
    }
    return res;
  }
  int query(int l, int r) {
    return query(r) - query(l-1);
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  ll v[7];
  for(int i=1;i<=6;i++) {
    cin>>v[i];
  }
  BIT bit[7];
  int p[n+1];
  for(int i=1;i<=n;i++) {
    char a;
    cin>>a;
    p[i] = a-'0';
    bit[p[i]].insert(i,1);
  }

  for(int i=0;i<m;i++) {
    int t,a,b;
    cin>>t>>a>>b;
    if(t==1) {
      bit[p[a]].insert(a,-1);
      p[a] = b;
      bit[p[a]].insert(a,1);
    } else if(t==2) {
      v[a] = b;
    } else {
      ll res = 0;
      for(int j=1;j<=6;j++) {
        res += bit[j].query(a,b) * v[j];
      }
      cout<<res<<nl;
    }
  }

  return 0;
}
