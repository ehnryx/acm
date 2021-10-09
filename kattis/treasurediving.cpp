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
  int id, dist;
  bool operator < (const Edge& o) const {
    return dist > o.dist;
  }
};

const int N = 1e4+1;
const int K = 9;
vector<Edge> adj[N];
map<int,vector<int>> interest;
bool vis[N];
int pos[K];
int dist[K][K];

void init(int n) {
  memset(dist, INF, sizeof dist);
  fill(adj, adj+n, vector<Edge>());
  interest.clear();
}

void dijkstra(int s) {
  memset(vis, 0, sizeof vis);
  priority_queue<Edge> dijk;
  dijk.push({s,0});
  while (!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if (!vis[cur.id]) {
      vis[cur.id] = true;
      if (interest.count(cur.id)) {
        for (int i : interest[s]) {
          for (int j : interest[cur.id]) {
            dist[i][j] = cur.dist;
          }
        }
      }
      for (const Edge& e : adj[cur.id]) {
        dijk.push({e.id, e.dist+cur.dist});
      }
    }
  }
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int T;
  cin >> T;
  while (T--) {
    int n, m, a, b, c;
    cin >> n >> m;
    init(n);
    for (int i=0; i<m; i++) {
      cin >> a >> b >> c;
      adj[a].push_back({b,c});
      adj[b].push_back({a,c});
    }

    vector<int> perm;
    int k;
    cin >> k;
    interest[0].push_back(0);
    for (int i=1; i<=k; i++) {
      cin >> pos[i];
      interest[pos[i]].push_back(i);
      perm.push_back(i);
    }

    for (int i=0; i<=k; i++) {
      dijkstra(pos[i]);
    }

    int cap;
    cin >> cap;
    int ans = 0;
    do {
      int cur = 0;
      int last = 0;
      for (int j=0; j<k; j++) {
        cur += dist[last][perm[j]];
        if (cur+dist[perm[j]][0] <= cap) {
          ans = max(ans, j+1);
        } else {
          break;
        }
        last = perm[j];
      }
    } while (next_permutation(perm.begin(), perm.end()));
    cout << ans << nl;
  }

  return 0;
}
