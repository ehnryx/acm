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

vector<string> keys = {
  "            ",
  " qwertyuiop ",
  " asdfghjkl  ",
  " zxcvbnm    ",
  "            ",
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  const int N = keys.size();
  const int M = keys[0].size();
  const int A = 128;
  int dist[A][A];
  memset(dist,INF,sizeof dist);
  for(int i=1;i<N-1;i++) {
    for(int j=1;j<M-1;j++) {
      if(isalpha(keys[i][j])) {
        dist[keys[i][j]][keys[i][j]] = 0;
        if(isalpha(keys[i-1][j])) dist[keys[i][j]][keys[i-1][j]] = 1;
        if(isalpha(keys[i+1][j])) dist[keys[i][j]][keys[i+1][j]] = 1;
        if(isalpha(keys[i][j-1])) dist[keys[i][j]][keys[i][j-1]] = 1;
        if(isalpha(keys[i][j+1])) dist[keys[i][j]][keys[i][j+1]] = 1;
      }
    }
  }
  for(int k=0;k<A;k++) {
    for(int i=0;i<A;i++) {
      for(int j=0;j<A;j++) {
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
      }
    }
  }

  int T;
  cin>>T;
  while(T--) {
    string s; int n;
    cin>>s>>n;
    vector<pair<int,string>> ans;
    for(int i=0;i<n;i++) {
      string t;
      cin>>t;
      int d = 0;
      for(int j=0;j<s.size();j++) {
        d += dist[s[j]][t[j]];
      }
      ans.push_back(make_pair(d,t));
    }
    sort(ans.begin(),ans.end());
    for(const auto& it:ans) {
      cout<<it.second<<" "<<it.first<<nl;
    }
  }

  return 0;
}
