#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5+1;
// Centroid decomposition: cent is child list, cpar is parent, d is depth
vector<int> adj[N], cent[N]; int d[N], sz[N], cpar[N];
void dfs(int u, int par) { sz[u] = 1; for (int v : adj[u])
    if (v != par && d[v] == -1) dfs(v, u), sz[u] += sz[v]; }
void decomp(int u, int par=-1) { for (int v : adj[u])
    if (d[v] == -1 && sz[v] > sz[u]/2) {
      sz[u] -= sz[v]; sz[v] += sz[u]; return decomp(v, par); }
  d[u] = d[par]+1; cpar[u] = par; if (par != -1) cent[par].push_back(u);
  for (int v : adj[u]) if (d[v] == -1) decomp(v, u); }
void init() { memset(d, -1, sizeof d); memset(cpar, -1, sizeof cpar);
  dfs(1, -1); decomp(1); }

unordered_map<int,int> nxt[N];
const int L = 18;
int anc[N][L];
int depth[N];
void build(int u, int p) {
  depth[u] = depth[p]+1;
  anc[u][0] = p;
  for(int j=1;j<L;j++) {
    anc[u][j] = anc[anc[u][j-1]][j-1];
  }
  for(int v:adj[u]) {
    if(v!=p) build(v,u);
  }
}

pii lca(int a, int b) {
  int u = a;
  if(depth[a]<depth[b]) swap(a,b);
  for(int j=L-1;j>=0;j--) {
    if(depth[anc[a][j]]>=depth[b]) a = anc[a][j];
  }
  if(a==b) {
    for(int j=L-1;j>=0;j--) {
      if(depth[anc[u][j]]>depth[b]) u = anc[u][j];
    }
    return pii(a,u);
  }
  for(int j=L-1;j>=0;j--) {
    if(anc[a][j]!=anc[b][j]) {
      a=anc[a][j];b=anc[b][j];
    }
  }
  return pii(anc[a][0],-1);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  for(int i=1;i<n;i++) {
    int a,b;
    cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  depth[0] = -1;
  build(1,0);

  init();
  int r = -1;
  for(int i=1;i<=n;i++) {
    if(cpar[i]!=-1) {
      int j,k;
      tie(j,k) = lca(i,cpar[i]);
      if(j==cpar[i]) j = k;
      else j = anc[cpar[i]][0];
      assert(j!=-1);
      nxt[cpar[i]][j] = i;
    } else r=i;
  }
  assert(r!=-1);

  for(;;) {
    cout << "? 2 " << r << endl;
    int v; cin >> v;
    assert(v!=-1);
    if (v==0) {
      cout << "! " << r << endl;
      return 0;
    } else {
      r = nxt[r][v];
    }
  }

  return 0;
}
