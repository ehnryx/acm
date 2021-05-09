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
random_device _rd; mt19937 rng(_rd());

namespace tarjan {
  //const int N = 2 * (130 * 2e4 + (1<<17));
  const int N = 2 * (2 * 2e4 + (1<<17));
  int low[N],vis[N],scomp[N],scompNum,I;
  vector<int> adj[N]; stack<int> verts;
  void init(int n) { for(int i=0; i<n; i++) adj[i].clear(); }
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v]=scompNum; }while (v != u);
      ++scompNum; }}
  void get_scc(int n) {
    memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
    scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }
  bool truth[N/2]; // N must be at least 2 times the number of variables
  // the clause a || b becomes !a => b and !b => a in implication graph
  void add_edge(int a, int b) {
    //cerr << "add edge " << (a%2?"!":"") << a/2 << " -> " << (b%2?"!":"") << b/2 << nl;
    adj[a].push_back(b);
  }
  void implies(int a, int b) { add_edge(a, b); add_edge(b^1, a^1); }
  void or_clause(int a, int b) { add_edge(a^1, b); add_edge(b^1, a); }
  bool two_sat(int n) { get_scc(n);
    for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return 0;
      truth[i/2] = (scomp[i] < scomp[i^1]); } return 1; }
}

void build(const vector<pair<int,int>>& x, int dx, int m, int off) {
  int n = size(x);
  for(int i=0, j=0; i<n; i++) {
    while(x[i].first - x[j].first > dx) j++;
    vector<int> top;
    for(int l=j+m, r=i+m; l<r; l/=2, r/=2) {
      if(l&1) top.push_back(l++);
      if(r&1) top.push_back(--r);
    }
    for(int s : top) {
      if(s < m) {
        tarjan::implies(2 * x[i].second, 2 * (off + s) + 1);
      } else {
        tarjan::implies(2 * x[i].second, 2 * (x[s - m].second) + 1);
      }
    }
    int s = i + m;
    tarjan::implies(2 * x[i].second, 2 * (off + s/2));
    for(s/=2; s>1; s/=2) {
      tarjan::implies(2 * (off + s), 2 * (off + s/2));
    }
  }
}

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

  int T;
  cin >> T;
  while(T--) {
    int n, dx, dy;
    cin >> n >> dx >> dy;
    int m = 1 << (32 - __builtin_clz(2*n-1));
    tarjan::init(2 * (2*n + 2*m));
    vector<pair<int,int>> x, y;
    for(int i=0; i<n; i++) {
      int k;
      cin >> k;
      if(k == 1) {
        int a, b;
        cin >> a >> b;
        x.emplace_back(a, 2*i);
        y.emplace_back(b, 2*i);
        x.emplace_back(a, 2*i + 1);
        y.emplace_back(b, 2*i + 1);
      } else {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        x.emplace_back(a, 2*i);
        y.emplace_back(b, 2*i);
        x.emplace_back(c, 2*i + 1);
        y.emplace_back(d, 2*i + 1);
      }
      tarjan::or_clause(2 * (2*i), 2 * (2*i + 1));
    }
    sort(begin(x), end(x));
    sort(begin(y), end(y));
    build(x, dx, m, 2*n);
    build(y, dy, m, 2*n + m);

    if(tarjan::two_sat(2 * (2*n + 2*m))) {
      cout << "Yes" << nl;
    } else {
      cout << "No" << nl;
    }
    //cerr << nl;
  }

  return 0;
}
