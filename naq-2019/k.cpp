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

vector<int> idx[26];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s;
  cin>>s;
  int n = s.size();
  for(int i=0;i<n;i++) {
    idx[s[i]-'a'].push_back(i);
  }
  for(int i=0;i<26;i++) {
    idx[i].push_back(n);
  }

  int ans = 0;
  for(int i=0;i<n;i++) {
    int c = s[i]-'a';
    int rb = *upper_bound(idx[c].begin(),idx[c].end(),i);
    for(int j=0;j<26;j++) {
      if(j==c) continue;
      int v = *upper_bound(idx[j].begin(),idx[j].end(),i);
      ans += (v < rb);
    }
  }
  cout<<ans<<nl;

  return 0;
}
