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
  ll cost;
  int parity;
  int source;
  Edge(){}
  Edge(int i, ll c, int p = 0, int s = -1):
    id(i), cost(c), parity(p), source(s) {}
  bool operator < (const Edge& v) const {
    return cost > v.cost;
  }
};

const int N = 1e5+1;
vector<Edge> adj[N];
int good[N];
ll dist[N][2];
ll source[N][2];

ll dijkstra(const vector<int>& t, pii& res) {
  memset(dist, INF, sizeof dist);
  priority_queue<Edge> todo;
  for (int i = 0; i < t.size(); i++) {
    todo.push(Edge(t[i], 0, i%2, t[i]));
  }

  while (!todo.empty()) {
    Edge cur = todo.top();
    todo.pop();

    if (dist[cur.id][cur.parity] == INFLL) {
      dist[cur.id][cur.parity] = cur.cost;
      source[cur.id][cur.parity] = cur.source;
      for (const Edge& e : adj[cur.id]) {
        if (dist[e.id][e.parity] == INFLL) {
          todo.push(Edge(e.id, e.cost + cur.cost, cur.parity, cur.source));
        }
      }
    }
  }

  ll mindist = INFLL;
  res = pii(-1,-1);
  for (int i = 0; i < t.size(); i++) {
    if (dist[t[i]][(i%2)^1] < mindist) {
      mindist = dist[t[i]][(i%2)^1];
      res = pii(t[i], source[t[i]][(i%2)^1]);
    }
  }
  return mindist;
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

  vector<int> type;
  for (int i = 1; i <= n; i++) {
    cin >> good[i];
    if (good[i]) {
      type.push_back(i);
    }
  }

  int a, b, c;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c;
    adj[a].push_back(Edge(b,c));
    adj[b].push_back(Edge(a,c));
  }

  pii ans(-1,-1);
  ll best = INFLL;
  while (clock() < 1.789*CLOCKS_PER_SEC) {
    shuffle(type.begin(), type.end(), rng);
    pii res;
    ll cur = dijkstra(type, res);
    if (cur < best) {
      ans = res;
      best = cur;
    }
  }

  if (ans.first == -1) {
    cout << "No luck at all" << nl;
  } else {
    cout << best << nl;
    cout << ans.first << " " << ans.second << nl;
  }

  return 0;
}
