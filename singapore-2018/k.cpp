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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const vector<int> dx = {0, 0, 1, -1};
const vector<int> dy = {1, -1, 0, 0};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> x(k), y(k);
  vector<char> put(k);
  map<pair<int,int>,int> have;
  vector<vector<pair<int,int>>> xline(n+1), yline(m+1);

  vector<vector<int>> adj(k);
  vector<vector<int>> graph(k);

  for(int i=0; i<k; i++) {
    cin >> x[i] >> y[i];
    have[pair(x[i], y[i])] = i;
    for(int d=0; d<4; d++) {
      int nx = x[i] + dx[d];
      int ny = y[i] + dy[d];
      if(have.count(pair(nx, ny))) {
        int nb = have[pair(nx, ny)];
        graph[nb].push_back(i);
        graph[i].push_back(nb);
      }
    }
    xline[x[i]].emplace_back(y[i], i);
    yline[y[i]].emplace_back(x[i], i);
  }

  stack<int> dfs;
  function<int(int,int)> build = [&](int u, int p) -> int {
    int sz = 1;
    for(int v : graph[u]) {
      if(v == p) continue;
      sz += build(v, u);
      adj[u].push_back(v);
      if(x[u] < x[v]) put[v] = '^';
      else if(x[u] > x[v]) put[v] = 'v';
      else if(y[u] < y[v]) put[v] = '<';
      else put[v] = '>';
    }
    return sz;
  };
  assert(build(0, -1) == k);

  auto add_edges = [&](const vector<pair<int,int>>& vec, int d, char want) {
    int last = 0;
    for(int i=0; i<vec.size(); i++) {
      if(i > 0 && vec[i-1].first == vec[i].first + d) {
        if(last) {
          last = vec[i].second;
          adj[vec[i-1].second].push_back(vec[i].second);
        }
      } else if(last) {
        adj[last].push_back(vec[i].second);
      }
      if(put[vec[i].second] == want) {
        last = vec[i].second;
      }
    }
  };

  for(auto& vec : xline) {
    if(vec.empty()) continue;
    sort(vec.begin(), vec.end());
    add_edges(vec, -1, '<');
    reverse(vec.begin(), vec.end());
    add_edges(vec, +1, '>');
  }

  for(auto& vec : yline) {
    if(vec.empty()) continue;
    sort(vec.begin(), vec.end());
    add_edges(vec, -1, '^');
    reverse(vec.begin(), vec.end());
    add_edges(vec, +1, 'v');
  }

  vector<int> deg(k);
  for(int i=0; i<k; i++) {
    for(int j : adj[i]) {
      deg[j]++;
    }
  }

  queue<int> bfs;
  for(int i=0; i<k; i++) {
    if(deg[i] == 0) {
      bfs.push(i);
    }
  }
  vector<int> order;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    order.push_back(u);
    for(int v : adj[u]) {
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }

  if(order.size() < k) {
    cout << "impossible" << nl;
  } else {
    cout << "possible" << nl;
    for(int i : order) {
      if(i == 0) continue;
      cout << put[i] << " " << (put[i] == '<' || put[i] == '>' ? x[i] : y[i]) << nl;
    }
  }

  return 0;
}
