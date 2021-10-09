//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 3000 + 1;
int dsu[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
int link(int i, int j) {
  i = find(i); j = find(j);
  if(i == j) return 0;
  dsu[i] = j;
  return 1;
}

struct Edge {
  int a, b, d, t;
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

int build(int n, int maxt, const vector<Edge>& edges) {
  memset(dsu, -1, sizeof dsu);
  int groups = n;
  int mind = INF;
  for(const auto& [a, b, d, t] : edges) {
    if(t > maxt) continue;
    if(link(a, b)) {
      groups--;
      mind = d;
    }
  }
  if(groups > 1) {
    mind = -1;
  }
  return mind;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m, q;
  cin >> n >> m >> q;
  vector<Edge> graph;
  vector<int> edges;
  for(int i=0; i<m; i++) {
    int a, b, d, t;
    cin >> a >> b >> d >> t;
    graph.push_back({a, b, d, t});
    edges.push_back(t);
  }

  sort(graph.begin(), graph.end());
  sort(edges.begin(), edges.end());
  edges.resize(unique(edges.begin(), edges.end()) - edges.begin());

  vector<int> mind(edges.size());
  for(int i=0; i<edges.size(); i++) {
    mind[i] = build(n, edges[i], graph);
  }

  for(int i=0; i<q; i++) {
    int a, b;
    cin >> a >> b;
    // durability >= a, time <= b
    int pos = upper_bound(edges.begin(), edges.end(), b) - edges.begin();
    if(pos == 0 || mind[pos-1] < a) {
      cout << "NO" << nl;
    } else {
      cout << "YES" << nl;
    }
  }

  return 0;
}
