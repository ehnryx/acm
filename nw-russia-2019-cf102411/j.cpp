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

const int N = 500+1;
char grid[N][N];
int g[N][N];
int adj[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      cin>>grid[i][j];
      g[i][j] = grid[i][j] - '0';
    }
  }

  for(int i=0;i<n;i++) {
    for(int j=i+1;j<n;j++) {
      int sum = 0;
      for(int k=i+1;k<j;k++) {
        sum += adj[i][k] * g[k][j] % 10;
      }
      if(sum%10 != g[i][j]) {
        adj[i][j] = 1;
      }
    }
  }

  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      cout<<adj[i][j];
    }
    cout<<nl;
  }

  return 0;
}
