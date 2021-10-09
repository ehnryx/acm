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

  int n;
  cin>>n;
  queue<string> nxt;
  for(int i=0;i<n;i++) {
    string name;
    cin>>name;
    nxt.push(name);
  }

  string s;
  cin>>s;
  s.push_back(0);

  string ba, bd, wa, wd;
  wa = nxt.front(); nxt.pop();
  ba = nxt.front(); nxt.pop();
  wd = nxt.front(); nxt.pop();
  bd = nxt.front(); nxt.pop();

  vector<pair<string,string>> ans;
  int best = 0;
  int cur = 0;
  char pre = 0;
  int cnt = 0;
  for(char c:s) {
    cerr<<wa<<" "<<wd<<" vs "<<ba<<" "<<bd<<nl;
    if(c == pre) {
      cur++;
    } else {
      if(cur > best) {
        ans.clear();
        best = cur;
      }
      if(cur == best) {
        if(pre == 'B') {
          if(cur%2 == 1) {
            ans.push_back(make_pair(ba,bd));
          } else {
            ans.push_back(make_pair(bd,ba));
          }
        } else {
          if(cur%2 == 1) {
            ans.push_back(make_pair(wa,wd));
          } else {
            ans.push_back(make_pair(wd,wa));
          }
        }
        if(cur==cnt) swap(ans.back().first, ans.back().second);
      }
      cur = 1;
    }
    if(c == 'W') {
      swap(wa,wd);
      nxt.push(bd);
      bd = ba;
      ba = nxt.front(); nxt.pop();
    } else {
      swap(ba,bd);
      nxt.push(wd);
      wd = wa;
      wa = nxt.front(); nxt.pop();
    }
    pre = c;
    cnt++;
  }

  for(const auto& it:ans) {
    cout<<it.first<<" "<<it.second<<nl;
  }

  return 0;
}
