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

const int N = 1e5+1;
vector<int> adj[N],rev[N];
int deg[N],vis[N];

void build(int u) {
  vis[u] = true;
  for(int v:rev[u]) {
    adj[u].push_back(v);
    deg[v]++;
    if(!vis[v]) {
      build(v);
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  string line;
  getline(cin,line);
  int n = stoi(line);
  unordered_map<string,int> idx;
  vector<string> name;
  for(int i=0;i<n;i++) {
    getline(cin,line);
    istringstream in(line);
    string cur; in>>cur; cur.pop_back();
    if(!idx.count(cur)) {
      idx[cur] = name.size();
      name.push_back(cur);
    }
    for(string s;in>>s;) {
      if(!idx.count(s)) {
        idx[s] = name.size();
        name.push_back(s);
      }
      rev[idx[s]].push_back(idx[cur]);
    }
  }
  getline(cin,line);
  build(idx[line]);

  queue<int> tos;
  tos.push(idx[line]);
  while(!tos.empty()) {
    int u = tos.front(); tos.pop();
    cout<<name[u]<<nl;
    for(int v:adj[u]) {
      if(--deg[v] == 0) {
        tos.push(v);
      }
    }
  }

  return 0;
}
