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

const int N = 1e5+1;
unordered_multiset<int> adj[N];
int vis[N],par[N],col[N],deg[N];

void build(int u, vector<pii>& edges, vector<int>& verts) {
  //cerr<<"@ "<<u<<nl;
  verts.push_back(u);
  vis[u] = true;
  vector<int> rem;
  while(!adj[u].empty()) {
    int v = *adj[u].begin();
    adj[u].erase(adj[u].begin());
    //cerr<<"vis "<<v<<nl;
    if(vis[v]) {
      //cerr<<"try to erase "<<u<<" from "<<v<<nl;
      assert(adj[v].count(u));
      adj[v].erase(adj[v].find(u));
      edges.push_back(pii(u,v));
    } else {
      assert(adj[v].count(u));
      //cerr<<"try to erase "<<u<<" from "<<v<<nl;
      adj[v].erase(adj[v].find(u));
      par[v] = u;
      build(v, edges, verts);
    }
  }
  //cerr<<" ret from "<<u<<nl;
}

int dsu[N];
int find(int i) {
  if(dsu[i]==-1) return i;
  return dsu[i]=find(dsu[i]);
}
void link(int i, int j) {
  if(find(i)!=find(j)) {
    dsu[find(i)] = find(j);
  }
}

void colour(int u) {
  if(par[u]==0) return;
  col[u] ^= 1;
  colour(par[u]);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n,m;
  cin>>n>>m;
  for(int i=0;i<m;i++) {
    int a,b;
    cin>>a>>b;
    adj[a].insert(b);
    adj[b].insert(a);
  }

  queue<int> rem;
  for(int i=1;i<=n;i++) {
    if(adj[i].size()<=2) {
      rem.push(i);
    }
  }

  int ans = 0;
  while(!rem.empty()) {
    int u = rem.front();
    rem.pop();
    if(adj[u].empty()) continue;
    if(adj[u].size()==1) {
      int v = *adj[u].begin();
      adj[v].erase(adj[v].find(u));
      if(!adj[v].empty() && adj[v].size() <= 2) rem.push(v);
    } else {
      int v = *adj[u].begin();
      int w = *next(adj[u].begin());
      adj[v].erase(adj[v].find(u));
      adj[w].erase(adj[w].find(u));
      if(v!=w) {
        adj[v].insert(w);
        adj[w].insert(v);
      } else {
        ans++;
      }
      if(!adj[v].empty() && adj[v].size() <= 2) rem.push(v);
      if(!adj[w].empty() && adj[w].size() <= 2) rem.push(w);
    }
    adj[u].clear();
  }

  vector<pii> edges;
  vector<int> verts;
  for(int i=1;i<=n;i++) {
    if(!adj[i].empty()) {
      build(i,edges,verts);
      break;
    }
  }

  int k = edges.size();
  for(int bm=1;bm<1<<k;bm++) {
    for(int i:verts) {
      dsu[i] = -1;
      deg[i] = 0;
    }
    int u = -1;
    for(int i=0;i<k;i++) {
      if(bm&1<<i) {
        int a,b;
        tie(a,b) = edges[i];
        colour(a);
        colour(b);
        link(a, b);
        deg[a]++;
        deg[b]++;
        u = a;
      }
    }
    for(int i:verts) {
      if(col[i]) {
        link(i, par[i]);
        deg[i]++;
        deg[par[i]]++;
      }
    }
    assert(u!=-1);
    int ref = find(u);
    bool good = true;
    for(int i=0;i<k;i++) {
      if(bm&1<<i) {
        if(find(edges[i].first) != ref) {
          good = false;
          break;
        }
      }
    }
    for(int i:verts) {
      good &= (deg[i] == 2 || deg[i] == 0);
    }
    ans += good;
    for(int i=0;i<k;i++) {
      if(bm&1<<i) {
        colour(edges[i].first);
        colour(edges[i].second);
      }
    }
  }
  cout<<ans<<nl;

  return 0;
}
