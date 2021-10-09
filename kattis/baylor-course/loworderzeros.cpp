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

vector<int> r = { 6, 2, 4, 8 };
const int N = 1e6+1;
int ans[N], two[N], five[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  ans[0] = 1;
  for(int i=1;i<N;i++) {
    two[i] = two[i-1];
    five[i] = five[i-1];
    int j = i;
    while(j%2==0) {
      two[i]++;
      j/=2;
    }
    while(j%5==0) {
      five[i]++;
      j/=5;
    }
    ans[i] = ans[i-1]*j % 10;
  }

  for(int n;cin>>n&&n;) {
    if(two[n]==five[n]) cout<<ans[n]<<nl;
    else cout << ans[n] * r[(two[n]-five[n])%4] % 10 << nl;
  }

  return 0;
}
