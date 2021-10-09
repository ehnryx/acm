#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int id, dist, pre;
  bool operator < (const Edge& o) const {
    return dist > o.dist;
  }
};

vector<int> dx = { 1, 1, 1, 0, 0, -1, -1, -1 };
vector<int> dy = { 1, 0, -1, 1, -1, 1, 0, -1 };

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  for (cin>>n>>m; n; cin>>n>>m) {
    auto get = [&] (int i, int j, int k) {
      return 2*(i*m+j)+k;
    };
    auto ret = [&] (int x) {
      return pii((x/2)/m, (x/2)%m);
    };

    string grid[n];
    vector<Edge> adj[2*n*m+2];
    for (int i=0; i<n; i++) {
      cin >> grid[i];
      for (int j=0; j<m; j++) {
        adj[get(i,j,0)].push_back({get(i,j,1), grid[i][j]-'0'});
        for (int k=0; k<8; k++) {
          int ni = i+dx[k];
          int nj = j+dy[k];
          if (0<=ni && ni<n && 0<=nj && nj<m) {
            adj[get(i,j,1)].push_back({get(ni,nj,0), 0});
          }
        }
      }
    }

    int source = 2*n*m;
    int sink = 2*n*m+1;
    for (int j=0; j<m; j++) {
      adj[source].push_back({get(0,j,0), 0});
      adj[get(n-1,j,1)].push_back({sink, 0});
    }

    int pre[2*n*m+2];
    memset(pre, -1, sizeof pre);

    priority_queue<Edge> dijk;
    dijk.push({source,0,source});
    while (!dijk.empty()) {
      Edge cur = dijk.top();
      dijk.pop();
      if (pre[cur.id] == -1) {
        pre[cur.id] = cur.pre;
        for (const Edge& e : adj[cur.id]) {
          dijk.push({e.id, e.dist+cur.dist, cur.id});
        }
      }
    }

    for (int i=pre[sink]; i!=source; i=pre[i]) {
      int x, y;
      tie(x,y) = ret(i);
      grid[x][y] = 0;
    }

    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (grid[i][j]) cout << grid[i][j];
        else cout << ' ';
      }
      cout << nl;
    }
    cout << nl;
  }

  return 0;
}
