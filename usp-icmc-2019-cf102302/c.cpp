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

const int N = 4e3+7;
int pre[N][N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  map<int,int> rmp;
  int a[n],b[n];
  for(int i=0;i<n;i++) {
    cin>>a[i]>>b[i];
    rmp[a[i]]; rmp[b[i]];
  }

  int id=0;
  for(auto& it:rmp) {
    it.second=++id;
  }

  for(int i=0;i<n;i++) {
    a[i]=rmp[a[i]];
    b[i]=rmp[b[i]];
    pre[a[i]][b[i]]=1;
  }
  for(int i=1;i<N;i++) {
    for(int j=1;j<N;j++) {
      pre[i][j]+=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
    }
  }
  
  auto sum = [&](int lx, int ly, int rx, int ry) {
    return pre[lx-1][ly-1]+pre[rx][ry]-pre[lx-1][ry]-pre[rx][ly-1];
  };

  int ans = 0;
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      if(a[i]<a[j] && b[i]<b[j]) {
        ans += (sum(a[i],b[i],a[j],b[j])==4 && sum(a[i],b[j],a[i],b[j]) && sum(a[j],b[i],a[j],b[i]));
      }
    }
  }
  cout<<ans<<nl;

  return 0;
}
