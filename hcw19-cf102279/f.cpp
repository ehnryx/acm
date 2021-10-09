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

const int N = 1<<17;
int s[2*N];
void build() {
  for(int i=N-1;i>0;i--) {
    s[i] = max(s[2*i],s[2*i+1]);
  }
}
int query(int l, int r) {
  int res = 0;
  for(l+=N,r+=N+1;l<r;l/=2,r/=2) {
    if(l&1) res = max(res, s[l++]);
    if(r&1) res = max(res, s[--r]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  int x[n],y[n];
  for(int i=0;i<n;i++) {
    cin>>x[i]>>y[i];
    s[i+N] = y[i];
  }
  build();

  ld ans = 0;
  for(int i=1;i<n;i++) {
    int h = min(query(0,i-1),query(i,n-1));
    int d = x[i]-x[i-1];
    int a = max(y[i],y[i-1]) - min(y[i],y[i-1]);
    h -= min(y[i],y[i-1]);
    if(h>=a) {
      ans += (ld)(h-a)*d + (ld)a*d/2;
    } else {
      ld dd = (ld)d*h/a;
      ans += (ld)h*dd/2;
    }
  }
  cout << ans << nl;

  return 0;
}
