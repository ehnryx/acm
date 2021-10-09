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

  string s;
  cin>>s;

  vector<pii> ans;
  unordered_map<int,set<int>> h, v;
  int x = 0;
  int y = 0;
  int d = 2;
  bool last = false;
  for(char c:s) {
    if(c=='L') {
      if(h[y].lower_bound(x) == h[y].begin()) {
        ans.push_back(make_pair(-d, y));
        h[y].insert(-d);
        x = -d + 1;
        last = true;
      } else {
        x = *prev(h[y].lower_bound(x)) + 1;
        last = false;
      }
    } else if(c=='R') {
      if(h[y].upper_bound(x) == h[y].end()) {
        ans.push_back(make_pair(d, y));
        h[y].insert(d);
        x = d - 1;
        last = true;
      } else {
        x = *h[y].upper_bound(x) - 1;
        last = false;
      }
    } else if(c=='U') {
      if(v[x].upper_bound(y) == v[x].end()) {
        ans.push_back(make_pair(x, d));
        v[x].insert(d);
        y = d - 1;
        last = true;
      } else {
        y = *v[x].upper_bound(y) - 1;
        last = false;
      }
    } else {
      if(v[x].lower_bound(y) == v[x].begin()) {
        ans.push_back(make_pair(x, -d));
        v[x].insert(-d);
        y = -d + 1;
        last = true;
      } else {
        y = *prev(v[x].lower_bound(y)) + 1;
        last = false;
      }
    }
    d += 2;
  }

  if(!last) {
    cout<<"impossible"<<nl;
  } else {
    cout<<-x<<" "<<-y<<nl;
    cout<<ans.size()<<nl;
    for(const auto& it:ans) {
      cout<<it.first-x<<" "<<it.second-y<<nl;
    }
  }

  return 0;
}
