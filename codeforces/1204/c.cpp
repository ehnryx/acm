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
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  int adj[n][n];
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      char c;
      cin>>c;
      if(c=='0') adj[i][j]=INF;
      else adj[i][j]=1;
    }
  }
  for(int i=0;i<n;i++) {
    adj[i][i]=0;
  }

  for(int k=0;k<n;k++) {
    for(int i=0;i<n;i++) {
      for(int j=0;j<n;j++) {
        adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
      }
    }
  }

  int m;
  cin>>m;
  int a[m];
  for(int i=0;i<m;i++) {
    cin>>a[i];
    --a[i];
  }

  vector<int> ans;
  ans.push_back(a[0]);
  for(int i=0;i<m-1;) {
    int j=i+1;
    while(j<m && adj[a[i]][a[j]]==j-i) j++;
    ans.push_back(a[--j]);
    i = j;
  }

  cout<<ans.size()<<nl;
  for(int it:ans) {
    cout<<it+1<<" ";
  }
  cout<<nl;

  return 0;
}
