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



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m,a,c,x0;
  cin>>n>>m>>a>>c>>x0;
  int x[n+1];
  x[0] = x0;
  for(int i=1;i<=n;i++) {
    x[i] = ((ll)a*x[i-1]+c) % m;
  }

  int ans = 0;
  for(int i=1;i<=n;i++) {
    int low = 1;
    int high = n;
    bool ok = false;
    while(low<=high) {
      int mid = (low+high)/2;
      if(x[mid] == x[i]) {
        ok = true;
        break;
      }
      if(x[i]<x[mid]) {
        high = mid-1;
      } else {
        low = mid+1;
      }
    }
    ans += ok;
  }
  cout<<ans<<nl;

  return 0;
}
