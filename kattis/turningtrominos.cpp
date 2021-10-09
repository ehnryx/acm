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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    ll a,b;
    cin>>a>>b;
    int ans = 0;
    for(int i=61;i>=0;i--) {
      ll v = 1LL<<i;
      if((a==v-1 && b==v) || (a==v && b==v-1)) {
        break;
      }
      if(a<v && b<v) {
      } else if(a<v) {
        ans++;
        b -= v;
        ll tmp = a;
        a = v-1-b;
        b = tmp;
      } else if(b<v) {
        ans--;
        a -= v;
        ll tmp = b;
        b = v-1-a;
        a = tmp;
      } else {
        a -= v;
        b -= v;
      }
    }
    cout<<(ans%4+4)%4<<nl;
  }

  return 0;
}
