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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);
const ld TOT = (21-5) * 60;

const int N = 100+1;
int a[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int n,w,s;
    cin>>n>>w>>s;
    int g = -1;
    for(int i=0;i<n;i++) {
      cin>>a[i];
      if(a[i]==0) {
        g = i;
      }
    }

    ld left = 0;
    ld right = 0;
    for(int i=0;i<n;i++) {
      if(i<g) {
        left = max(left, atan2(a[i], (ld)(g-i)*(w+s)));
      }
      if(i>g) {
        right = max(right, atan2(a[i], (ld)(i-g)*(w+s)));
      }
    }
    cout << (PI-left-right)/PI * TOT << nl;
  }

  return 0;
}
