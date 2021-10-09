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
  Edge(int i, int d): id(i), dist(d) {}
};

struct Pos {
  int x, y, z;
  Pos() {}
  Pos(int x, int y, int z): x(x), y(y), z(z) {}
};

struct Node {
  int x, y, z;
  int dist;
  Node() {}
  Node(int x, int y, int z, int d): x(x), y(y), z(z), dist(d) {}
  bool operator < (const Node& other) const {
    return dist > other.dist;
  }
};

int dist[51][51][51];
int minpush[51][51][51];
vector<Edge> comp[3][51];
vector<Node> graph[51][51][51];

int dijkstra(const Pos& s, const Pos& t, int var) {
  memset(dist, -1, sizeof dist);
  memset(minpush, INF, sizeof minpush);

  priority_queue<Node> next;
  next.push(Node(s.x, s.y, s.z, 0));

  while (!next.empty()) {
    Node cur = next.top();
    next.pop();
    if (dist[cur.x][cur.y][cur.z] == -1) {
      if (cur.x == t.x && cur.y == t.y && cur.z == t.z) return cur.dist;
      dist[cur.x][cur.y][cur.z] = cur.dist;
      for (const Edge& ex : comp[0][cur.x]) {
        for (const Edge& ey : comp[1][cur.y]) {
          for (const Edge& ez : comp[2][cur.z]) {
            int nd = ex.dist + ey.dist + ez.dist + cur.dist;
            if (nd < minpush[ex.id][ey.id][ez.id]) {
              next.push(Node(ex.id, ey.id, ez.id, nd));
              minpush[ex.id][ey.id][ez.id] = nd;
            }
          }
        }
      }
    }
  }

  return dist[t.x][t.y][t.z];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  srand(time(nullptr));

  vector<int> source, dest, sz;
  unordered_set<int> var;

  int countries;
  cin >> countries;

  for (int p = 0; p < countries; p++) {
    int n, m;
    cin >> n >> m;
    sz.push_back(n);

    int a, b, c;
    for (int i = 1; i <= n; i++) {
      cin >> c;
      comp[p][i].push_back(Edge(i, c));
      var.insert(c);
    }
    for (int i = 0; i < m; i++) {
      cin >> a >> b >> c;
      comp[p][a].push_back(Edge(b, c));
      var.insert(c);
    }
    cin >> a;
    source.push_back(1);
    dest.push_back(a);
  }
  for (int p = countries; p < 3; p++) {
    sz.push_back(1);
    comp[p][1].push_back(Edge(1, 0));
    source.push_back(1);
    dest.push_back(1);
  }

  cout << dijkstra(Pos(source[0], source[1], source[2]), Pos(dest[0], dest[1], dest[2]), var.size()) << nl;

  return 0;
}
