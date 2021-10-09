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

const int N = 1<<18;
int st[2*N];
void insert(int l, int r, int v) {
  for(l+=N,r+=N+1; l<r; l/=2,r/=2) {
    if(l&1) { st[l] = min(st[l], v); l++; }
    if(r&1) { --r; st[r] = min(st[r], v); }
  }
}
int query(int x) {
  int res = st[x+=N];
  for(x/=2;x;x/=2) {
    res = min(res, st[x]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  int a[n],s[n];
  for(int i=0;i<n;i++) {
    cin>>a[i]>>s[i];
  }

  memset(st,INF,sizeof st);
  insert(0,0,0);
  for(int i=1;i<=2*m;i++) {
    for(int j=0;j<n;j++) {
      int lb = a[j]-s[j];
      int ub = a[j]+s[j];
      int inc = max(0, i-ub);
      int cost = inc + query(max(0,lb-inc-1));
      insert(0, min(m,ub+inc), cost);
    }
  }
  cout<<query(m)<<nl;

  return 0;
}
