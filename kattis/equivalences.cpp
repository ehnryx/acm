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

const int N = 2e4+1;
namespace SCC {
  int low[N],vis[N],scomp[N],scompNum,I;
  vector<int> adj[N]; stack<int> verts;
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v != u);
      ++scompNum; }}
  void get_scc(int n) { fill(vis,vis+n+1,0); fill(scomp,scomp+n+1,-1);
    scompNum=I=0; for (int i=1; i<=n; ++i) if (!vis[i]) scc(i); }
  void init(int n) {
    fill(adj,adj+n+1,vector<int>());
  }
}

const int M = 5e4+1;
int a[M], b[M];
int in[N],out[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int n,m;
    cin>>n>>m;
    SCC::init(n);
    for(int i=0;i<m;i++) {
      cin>>a[i]>>b[i];
      SCC::adj[a[i]].push_back(b[i]);
    }
    SCC::get_scc(n);
    if(SCC::scompNum==1) {
      cout<<0<<nl;
      continue;
    }

    fill(in,in+SCC::scompNum,0);
    fill(out,out+SCC::scompNum,0);
    for(int i=0;i<m;i++) {
      if(SCC::scomp[a[i]] != SCC::scomp[b[i]]) {
        in[SCC::scomp[b[i]]]++;
        out[SCC::scomp[a[i]]]++;
      }
    }
    int icnt=0;
    int ocnt=0;
    for(int i=0;i<SCC::scompNum;i++) {
      if(!in[i]) icnt++;
      if(!out[i]) ocnt++;
    }
    cout<<max(icnt,ocnt)<<nl;
  }

  return 0;
}
