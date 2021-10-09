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

  int n;
  cin>>n;
  string s[n+1];
  list<char> t[n+1];
  for(int i=1;i<=n;i++) {
    cin>>s[i];
    for(char c:s[i]) {
      t[i].push_back(c);
    }
  }
  int last = 1;
  for(int i=1;i<n;i++) {
    int a,b;
    cin>>a>>b;
    last = a;
    if(t[a].size() < t[b].size()) {
      t[b].insert(t[b].begin(),t[a].begin(),t[a].end());
      swap(t[a],t[b]);
    } else {
      t[a].insert(t[a].end(),t[b].begin(),t[b].end());
    }
  }
  for(char c:t[last]) {
    putchar(c);
  }
  putchar(nl);

  return 0;
}
