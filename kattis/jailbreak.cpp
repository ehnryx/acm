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

struct Edge {
  int i,d;
};

const int N = 100;
const int M = N*N+1;
string g[N];
vector<Edge> adj[M];
int from_s[M], from_p1[M], from_p2[M];

void dijkstra(int s, int dist[]) {
  fill(dist,dist+M,INF);
  deque<Edge> dijk;
  dijk.push_back({s,0});
  while(!dijk.empty()) {
    Edge cur = dijk.front();
    dijk.pop_front();
    if(dist[cur.i]<INF) continue;
    dist[cur.i] = cur.d;
    for(const Edge& e:adj[cur.i]) {
      if(dist[e.i]<INF) continue;
      if(e.d) dijk.push_back({e.i,e.d+cur.d});
      else dijk.push_front({e.i,e.d+cur.d});
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) {
      cin>>g[i];
    }
    auto get = [&](int i, int j) {
      return i*m+j;
    };

    fill(adj,adj+n*m+1,vector<Edge>());
    int s = n*m;
    vector<int> ppl;
    for(int i=0;i<n;i++) {
      for(int j=0;j<m;j++) {
        if(g[i][j] == '*') continue;
        int c = (g[i][j] == '#');
        int id = get(i,j);
        if(g[i][j] == '$') ppl.push_back(id);
        if(i>0) {
          adj[id].push_back({get(i-1,j),c});
        } else {
          adj[id].push_back({s,c});
          adj[s].push_back({id,0});
        }
        if(j>0) {
          adj[id].push_back({get(i,j-1),c});
        } else {
          adj[id].push_back({s,c});
          adj[s].push_back({id,0});
        }
        if(i+1<n) {
          adj[id].push_back({get(i+1,j),c});
        } else {
          adj[id].push_back({s,c});
          adj[s].push_back({id,0});
        }
        if(j+1<m) {
          adj[id].push_back({get(i,j+1),c});
        } else {
          adj[id].push_back({s,c});
          adj[s].push_back({id,0});
        }
      }
    }
    dijkstra(s, from_s);
    dijkstra(ppl[0], from_p1);
    dijkstra(ppl[1], from_p2);
    assert(ppl.size()==2);

    int ans = INF;
    for(int i=0;i<n;i++) {
      for(int j=0;j<m;j++) {
        if(g[i][j] != '*') {
          int id = get(i,j);
          ans = min(ans, from_s[id]+from_p1[id]+from_p2[id] + (g[i][j]=='#'));
        }
      }
    }
    cout<<ans<<nl;
  }

  return 0;
}
