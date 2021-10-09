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



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int lb = -INF;
  int ub = INF;
  for(int n;cin>>n&&n;) {
    string s;
    cin>>s>>s;
    if(s=="high") {
      ub = min(ub,n);
    } else if(s=="low") {
      lb = max(lb,n);
    } else {
      if(lb<n && n<ub) {
        cout<<"Stan may be honest"<<nl;
      } else {
        cout<<"Stan is dishonest"<<nl;
      }
      lb = -INF;
      ub = INF;
    }
  }

  return 0;
}
