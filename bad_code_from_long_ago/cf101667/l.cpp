#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Edge {
  int id;
  int dist;
  Edge() {}
  Edge(int i, int dist): id(i), dist(dist) {}
};

const int LIM = 50*49*47;
const int distlim = 50e6;

ll dist[3][51][LIM+1];
vector<Edge> graph[3][51];
int dest[3];

void dijkstra(int g, int s, int t) {
  memset(dist[g], INF, sizeof dist[g]);

  queue<pii> next;
  next.push(pii(s, 0));
  dist[g][s][0] = 0;


  while (!next.empty()) {
    pii cur = next.front(); 
    next.pop();
    for (const Edge& e : graph[g][cur.first]) {
      if (cur.second < LIM) {
        if (dist[g][e.id][cur.second+1] == INFLL) {
          next.push(pii(e.id, cur.second + 1));
        }
        dist[g][e.id][cur.second+1] = min(dist[g][e.id][cur.second+1], e.dist + dist[g][cur.first][cur.second]);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int countries;
  cin >> countries;

  for (int p = 0; p < countries; p++) {
    int n, m;
    cin >> n >> m;

    int a, b, c;
    for (int i = 1; i <= n; i++) {
      cin >> c;
      graph[p][i].push_back(Edge(i, c));
    }
    for (int i = 0; i < m; i++) {
      cin >> a >> b >> c;
      graph[p][a].push_back(Edge(b, c));
    }
    cin >> dest[p];

    dijkstra(p, 1, dest[p]);
  }


  ll ans = INF;
  for (int i = 0; i <= LIM; i++) {
    ll sum = 0;
    for (int p = 0; p < countries; p++)
      sum += dist[p][dest[p]][i];
    if (sum > 0)
      ans = min(ans, sum);
  }
  cout << ans << nl;

  return 0;
}
