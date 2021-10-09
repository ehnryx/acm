//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "electricity"

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

struct Edge {
  int v, c, i;
  Edge(int _v, int _c, int _i): v(_v), c(_c), i(_i) {}
};

const int N = 1e3 + 1;
vector<Edge> adj[N];
int dist[N], in[N];
bool out[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  int n, m;
  cin >> n >> m;
  int need = 0;
  vector<int> rev(m+1);
  for(int i=1; i<=m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c, i);
    if(c) {
      rev[i] = adj[b].size();
      adj[b].emplace_back(a, -1, i);
      out[a] = true;
      need++;
    }
  }

  vector<int> ans;
  while(ans.size() < need) {
    memset(dist, -1, sizeof dist);
    memset(in, 0, sizeof in);
    for(int i=1; i<=n; i++) {
      for(const auto& [v, c, _] : adj[i]) {
        if(c != -1) {
          in[v]++;
        }
      }
    }

    queue<int> bfs;
    for(int i=1; i<=n; i++) {
      if(in[i] == 0) {
        bfs.push(i);
        dist[i] = 0;
      }
    }
    while(!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      for(const auto& [v, c, _] : adj[u]) {
        if(c != -1) {
          dist[v] = max(dist[v], dist[u] + 1);
          if(--in[v] == 0) {
            bfs.push(v);
          }
        }
      }
    }

    int cur = -1;
    for(int i=1; i<=n; i++) {
      if(out[i]) {
        if(cur == -1 || dist[i] > dist[cur]) {
          cur = i;
        }
      }
    }

    out[cur] = false;
    unordered_set<int> seen;
    vector<pair<int,int>> order;
    for(auto& [v, c, i] : adj[cur]) {
      if(c == 1) {
        c = -1;
        adj[v][rev[i]].c = 0;
        order.emplace_back(dist[v], i);
        if(!seen.insert(v).second) {
          cout << -1 << nl;
          return 0;
        }
      }
    }
    sort(order.begin(), order.end());
    for(const auto& [_, i] : order) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << nl;
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
