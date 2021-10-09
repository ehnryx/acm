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
  int id;
  ll dist;
  int pre;

  Edge(){}
  Edge(int i, ll d = 0, int p = 0): id(i), dist(d), pre(p) {}
  bool operator < (const Edge& e) const {
    return dist > e.dist;
  }
};

const int N = 1e5+1;
vector<Edge> adj[N];
ll dist[N];
int pre[N];

vector<int> dijkstra(int s, int t) {
  memset(dist, -1, sizeof dist);
  priority_queue<Edge> nxt;

  nxt.push(Edge(s));
  while (!nxt.empty()) {
    Edge cur = nxt.top();
    nxt.pop();

    if (dist[cur.id] == -1) {
      dist[cur.id] = cur.dist;
      pre[cur.id] = cur.pre;
      for (const Edge& e : adj[cur.id]) {
        nxt.push(Edge(e.id, cur.dist + e.dist, cur.id));
      }
    }
  }

  if (dist[t] == -1) {
    return { -1 };
  } else {
    vector<int> res;
    for (int i = t; i != 0; i = pre[i]) {
      res.push_back(i);
    }
    reverse(res.begin(), res.end());
    return res;
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

  int n, m;
  cin >> n >> m;

  int a, b, c;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c;
    adj[a].push_back(Edge(b,c));
    adj[b].push_back(Edge(a,c));
  }

  for (int i : dijkstra(1, n)) {
    cout << i << " ";
  }
  cout << nl;

  return 0;
}
