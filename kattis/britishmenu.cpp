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

// MAGIC IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

const int N = 1e5+1;

namespace Tarjan {
  int low[N],vis[N],scomp[N],scompNum,I;
  vector<int> adj[N]; stack<int> verts;
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v != u);
      ++scompNum; }}
  void get_scc(int n) { memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
    scompNum=I=0; for (int i=1; i<=n; ++i) if (!vis[i]) scc(i); }
}

struct Edge {
  int id,i,j;
};

vector<Edge> dag[N];
int in[N];

vector<int> scc[N];
int remap[N];
vector<pii> edges[N];
int dist[N][5][5];
int dpi[N][5], dp[N][5];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  //cin>>n>>m;
  read(n);read(m);
  for(int i=0;i<m;i++) {
    int a,b;
    //cin>>a>>b;
    read(a);read(b);
    Tarjan::adj[a].push_back(b);
  }
  Tarjan::get_scc(n);

  for(int i=1;i<=n;i++) {
    int id = Tarjan::scomp[i];
    remap[i] = scc[id].size();
    scc[id].push_back(i);
    for(int j:Tarjan::adj[i]) {
      int cur = Tarjan::scomp[j];
      if(cur==id) {
        edges[id].push_back(pii(i,j));
      } else {
        dag[id].push_back({cur,i,j});
        in[cur]++;
      }
    }
  }

  queue<int> bfs;
  int sad[5][5];
  for(int i=0;i<Tarjan::scompNum;i++) {
    int sz = scc[i].size();
    memset(sad,0,sizeof sad);
    for(const pii& e:edges[i]) {
      sad[remap[e.first]][remap[e.second]] = 1;
    }

    vector<int> p;
    for(int j=0;j<sz;j++) {
      p.push_back(j);
    }
    do {
      dist[i][p[0]][p[0]] = 1;
      for(int j=1;j<sz;j++) {
        if(sad[p[j-1]][p[j]]) {
          dist[i][p[0]][p[j]] = max(dist[i][p[0]][p[j]], j+1);
        } else {
          break;
        }
      }
    } while(next_permutation(p.begin(),p.end()));

    if(in[i]==0) {
      bfs.push(i);
    }
  }

  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    int sz = scc[u].size();
    for(int i=0;i<sz;i++) {
      for(int j=0;j<sz;j++) {
        dp[u][j] = max(dp[u][j], dpi[u][i] + dist[u][i][j]);
      }
    }
    for(const Edge& e:dag[u]) {
      dpi[e.id][remap[e.j]] = max(dpi[e.id][remap[e.j]], dp[u][remap[e.i]]);
      if(--in[e.id] == 0) {
        bfs.push(e.id);
      }
    }
  }

  int ans = 0;
  for(int i=0;i<N;i++) {
    for(int j=0;j<5;j++) {
      ans = max(ans,dp[i][j]);
    }
  }
  cout<<ans<<nl;

  return 0;
}

