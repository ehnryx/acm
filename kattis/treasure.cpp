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

struct Node {
  int a,b,d;
  bool operator < (const Node& o) const {
    return d > o.d;
  }
};

vector<int> dx = { 0, 0, 1, -1 };
vector<int> dy = { 1, -1, 0, 0 };

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  map<char,int> get_cost;
  get_cost['S'] = get_cost['G'] = get_cost['.'] = 1;
  get_cost['F'] = 2;
  get_cost['M'] = 3;
  get_cost['#'] = INF;

  int n,m,k;
  cin>>n>>m>>k;

  string g[n];
  pii s,t;
  for(int i=0;i<n;i++) {
    cin>>g[i];
    for(int j=0;j<m;j++) {
      if(g[i][j]=='S') {
        s = make_pair(i,j);
      }
      if(g[i][j]=='G') {
        t = make_pair(i,j);
      }
    }
  }

  int dist[n][m];
  memset(dist,INF,sizeof dist);

  priority_queue<Node> dijk;
  dijk.push({s.first,s.second,0});
  while(!dijk.empty()) {
    Node cur = dijk.top();
    dijk.pop();
    if(dist[cur.a][cur.b]==INF) {
      dist[cur.a][cur.b] = cur.d;
      for(int d=0;d<4;d++) {
        int ni = cur.a+dx[d];
        int nj = cur.b+dy[d];
        if(0<=ni&&ni<n && 0<=nj&&nj<m && get_cost[g[ni][nj]]<=k) {
          int cost = get_cost[g[ni][nj]];
          int nd = cur.d+cost;
          if(nd > (cur.d/k+1)*k) {
            nd = (cur.d/k+1)*k + cost;
          }
          dijk.push({ni,nj,nd});
        }
      }
    }
  }
  if(dist[t.first][t.second] == INF) {
    cout<<-1<<nl;
  } else {
    cout<<(dist[t.first][t.second]+k-1)/k<<nl;
  }

  return 0;
}
