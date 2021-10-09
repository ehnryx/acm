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

namespace MinArb {
  const int N = 1e3+1;
  const int M = 5e5;
  int first[N], nxt[2*M], ep[2*M], par[N], m; ll cost[2*M], cur_cost[N];
  bool seen[N], seen2[N]; int parent[N];
  void init() { m = 0; memset(first, -1, sizeof first); }
  void add_edge(int a, int b, ll c) {
    ep[m]=a; nxt[m]=first[a]; first[a]=m; cost[m]=c; cost[++m]=c; ep[m++]=b; }
  int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }
  void merge(int x, int y) { parent[find(x)] = find(y); }
  ll find_and_break_cycle(int x, int n) { memset(seen2, 0, sizeof seen2); int y;
    for(y=find(x);!seen2[y]&&y!=0;y=find(ep[par[y]^1])) seen[y]=seen2[y]=true;
    if (y == 0) return 0; // no cycle
    vector<int> saved(parent, parent+n), cycle;
    for(int p;(p=find(ep[par[y]^1]))!=y;y=p){cycle.push_back(par[y]); merge(y,p);}
    cycle.push_back(par[y]);
    // find cheapest reweighted incoming edge
    ll best = INF; int edge = -1, y_root = find(y);
    for (int i = 1; i < n; ++i) if (find(i) == y_root) {
      for (int e=first[i]; e != -1; e = nxt[e]) if (find(ep[e^1]) != y_root) {
        if ((cost[e] -= cur_cost[i]) < best) { best = cost[e], edge = e; } } }
    for (int i = 1; i < n; ++i) if (find(i) == y_root) cur_cost[i] = best;
    assert(edge != -1); par[y_root] = edge;
    ll ans = best + find_and_break_cycle(y_root, n);
    edge = par[y_root]; for (int i = 0; i < n; ++i) parent[i] = saved[i];
    par[find(ep[edge])] = edge;
    for (int i=0; i < cycle.size(); ++i) if (find(ep[cycle[i]]) != find(ep[edge]))
      par[find(ep[cycle[i]])] = cycle[i];
    return ans; }
  // the MST is rooted at vertex 0
  ll directed_MST(int n) { ll ans = 0; memset(cur_cost, 0x3f, sizeof(cur_cost));
    for(int i = 0; i < n; ++i) parent[i] = i;
    // use minimum incoming edge
    for (int i = 1; i < n; ++i) {
      for (int e=first[i]; e != -1; e = nxt[e]) {
        if (cost[e] < cur_cost[i]) { cur_cost[i] = cost[e]; par[i] = e; } }
      ans += cur_cost[i]; }
    memset(seen, 0, sizeof seen);
    for (int i = 1; i < n; ++i) if (!seen[find(i)])
      ans += find_and_break_cycle(i, n);
    return ans; }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  for(int tt=1;tt<=T;tt++) {
    int n,m;
    cin>>n>>m;
    MinArb::init();
    for(int i=0;i<m;i++) {
      int a,b,c;
      cin>>a>>b>>c;
      MinArb::add_edge(b,a,c);
    }
    for(int i=1;i<n;i++) {
      MinArb::add_edge(i,0,INF);
    }
    cout<<"Case #"<<tt<<": ";
    ll ans = MinArb::directed_MST(n);
    if(ans >= INF) {
      cout<<"Possums!"<<nl;
    } else {
      cout<<ans<<nl;
    }
  }

  return 0;
}
