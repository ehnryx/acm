//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string line;
  getline(cin, line);
  int n = stoi(line);
  unordered_map<string,int> idx;
  vector<string> names;
  vector<vector<int>> adj;
  for(int i=0, sid=0; i<n; i++) {
    getline(cin, line);
    istringstream in(line);
    string s;
    in >> s;
    if(!idx.count(s)) {
      idx[s] = sid++;
      names.push_back(s);
      adj.push_back(vector<int>());
    }
    int u = idx[s];
    while(in >> s) {
      if(!idx.count(s)) {
        idx[s] = sid++;
        names.push_back(s);
        adj.push_back(vector<int>());
      }
      int v = idx[s];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  string s, t;
  cin >> s >> t;
  if(!idx.count(s) || !idx.count(t)) {
    cout << "no route found" << nl;
    return 0;
  }

  int goal = idx[t];
  queue<int> bfs;
  bfs.push(idx[s]);
  vector<int> pre(idx.size(), -1);
  pre[idx[s]] = idx[s];
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    if(u == goal) break;
    for(int v : adj[u]) {
      if(pre[v] == -1) {
        pre[v] = u;
        bfs.push(v);
      }
    }
  }

  if(pre[goal] == -1) {
    cout << "no route found" << nl;
    return 0;
  }

  vector<string> ans;
  for(int u=goal; u!=idx[s]; u=pre[u]) {
    ans.push_back(names[u]);
  }
  ans.push_back(names[idx[s]]);
  reverse(ans.begin(), ans.end());

  for(const string& it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
