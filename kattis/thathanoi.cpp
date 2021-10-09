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

int N[3];
vector<int> v[3];
int id[51];
ll solve(int n, int a, int b, int c) {
  if(n==0) return 0;
  if(id[n]==c) return -INFLL;
  if(id[n]==a) return (1LL<<(n-1)) + solve(n-1, a, c, b);
  return solve(n-1, c, b, a);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  for(int i=0;i<3;i++) {
    cin>>N[i];
    v[i].resize(N[i]);
    for(int j=0;j<N[i];j++) {
      cin>>v[i][j];
      id[v[i][j]] = i;
      if(j>0 && v[i][j]>v[i][j-1]) {
        cout<<"No"<<nl;
        return 0;
      }
    }
  }
  ll ans = solve(N[0]+N[1]+N[2], 0, 2, 1);
  if(ans<0) cout<<"No"<<nl;
  else cout<<ans<<nl;

  return 0;
}
