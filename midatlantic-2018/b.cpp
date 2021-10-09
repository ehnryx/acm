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

int get_num(const string& s, int& i) {
  int res = 0;
  while(isdigit(s[i])) {
    res = res*10 + s[i++]-'0';
  }
  return res;
}

bool is_cycle(const vector<vector<int>>& adj, vector<bool>& vis, int u) {
  vis[u] = true;
  bool ok = (adj[u].size()==2);
  for(int v:adj[u]) {
    if(!vis[v]) {
      ok &= is_cycle(adj,vis,v);
    }
  }
  return ok;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  map<pii,int> idx;
  int id = 0;
  vector<vector<int>> adj;
  for(string s;getline(cin,s);) {
    vector<int> vals;
    for(int i=0;i<s.size();i++) {
      if(s[i]==';') {
        assert(vals.size()==4);
        pii a(vals[0],vals[1]);
        pii b(vals[2],vals[3]);
        vals.clear();
        if(!idx.count(a)) {
          idx[a] = id++;
          adj.push_back(vector<int>());
        }
        if(!idx.count(b)) {
          idx[b] = id++;
          adj.push_back(vector<int>());
        }
        adj[idx[a]].push_back(idx[b]);
        adj[idx[b]].push_back(idx[a]);
      } else if(isdigit(s[i])) {
        vals.push_back(get_num(s,i));
      }
    }
  }

  int fig = 0;
  int cyc = 0;
  vector<bool> vis(id);
  for(int i=0;i<id;i++) {
    if(!vis[i]) {
      fig += 1;
      cyc += is_cycle(adj,vis,i);
    }
  }
  cout<<fig<<" "<<cyc<<nl;

  return 0;
}
