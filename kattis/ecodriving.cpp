#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld sqr(ld x) { return x*x; }

struct Edge {
  int i,r; ld d;
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

const int N = 200+1;
vector<Edge> adj[N];
int x[N],y[N];
ld edge[N][N];
ld dist[N][N];

ld angle(int a, int b, int c) {
  ld dot = (ld)(x[b]-x[a])*(x[c]-x[b]) + (ld)(y[b]-y[a])*(y[c]-y[b]);
  dot /= edge[a][b] * edge[b][c];
  return acos(dot);
}

bool valid(ld ub, int n, int d) {
  fill(&dist[0][0],&dist[0][0]+N*N,INF);
  priority_queue<Edge> dijk;
  for(const Edge& e:adj[1]) {
    dijk.push({e.i,1,e.d});
    dist[e.i][1] = e.d;
  }
  while(!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if(cur.d > d+EPS) return false;
    if(cur.i == n) return true;
    if(cur.d > dist[cur.i][cur.r]) continue;
    for(const Edge& e:adj[cur.i]) {
      if(angle(cur.r,cur.i,e.i) < ub && cur.d+e.d < dist[e.i][e.r]) {
        dist[e.i][e.r] = cur.d+e.d;
        dijk.push({e.i,e.r,cur.d+e.d});
      }
    }
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n,m,d;
  cin>>n>>m>>d;
  for(int i=1;i<=n;i++) {
    cin>>x[i]>>y[i];
  }
  for(int i=0;i<m;i++) {
    int a,b;
    cin>>a>>b;
    edge[a][b] = edge[b][a] = sqrt(sqr(x[a]-x[b])+sqr(y[a]-y[b]));
    adj[a].push_back({b,a,edge[a][b]});
  }

  ld l = 0;
  ld r = M_PI + 0.1;
  while(r-l>EPS) {
    ld mid = (l+r)/2;
    if(valid(mid,n,d)) {
      r = mid;
    } else {
      l = mid;
    }
  }

  if(r>M_PI+EPS) {
    cout<<"Impossible"<<nl;
  } else {
    cout<<l*180/M_PI<<nl;
  }

  return 0;
}
