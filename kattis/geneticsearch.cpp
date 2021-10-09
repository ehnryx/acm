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

  for(string s,t;cin>>s>>t;) {
    swap(s,t);
    int n=s.size(); int m=t.size();
    unordered_set<string> tt[3];
    vector<int> ans(3);
    tt[1].insert(t);
    for(int j=0;j<=m;j++) {
      if(j<m) tt[0].insert(t.substr(0,j) + t.substr(j+1));
      for(string c:{"A","G","C","T"}) {
        tt[2].insert(t.substr(0,j) + c + t.substr(j));
      }
    }
    s += "eyqs";
    for(int i=0;i+m-1<=n;i++) {
      for(int j=0;j<3;j++) {
        for(const string& ss:tt[j]) {
          ans[j] += (s.substr(i,m+j-1) == ss);
        }
      }
    }
    cout<<ans[1]<<" "<<ans[0]<<" "<<ans[2]<<nl;
  }

  return 0;
}
