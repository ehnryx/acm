#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;


int h, w;
int convert(int x, int y) {
  return x*w + y;
}

struct Graph {
  int vertices;
  vector<vector<int>> g;
  vector<int> depth;
  Graph(int n) {
    vertices = n;
    g.resize(n);
    depth.resize(n);
  }
  void add_edge(int a, int b) {
    g[a].push_back(b);
  }
  ll search(int s) {
    struct Node {
      int id;
      int depth;
      Node(int id=-1, int depth=-1) {
        this->id = id;
        this->depth = depth;
      }
      bool operator < (const Node& other) const {
        return other.depth < this->depth;
      }
    };
    ll ans = 0;
    vector<bool> visited(vertices);
    priority_queue<Node> next;
    next.push(Node(s, depth[s]));
    Node cur;
    while (!next.empty()) {
      cur = next.top(); next.pop();
      if (cur.depth >= 0)
        break;
      if (!visited[cur.id]) {
        //cerr << "curid: " << cur.id << "  depth: " << cur.depth << nl;
        visited[cur.id] = true;
        ans += -cur.depth;
        for (int neighbour : g[cur.id]) {
          if (!visited[neighbour]) {
            next.push(Node(neighbour, max(cur.depth, depth[neighbour])));
          }
        }
      }
    }
    return ans;
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int x, y;
  cin >> h >> w;
  Graph graph(h*w);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      cin >> graph.depth[convert(i,j)];
      if (i > 0 && j > 0) graph.add_edge(convert(i,j), convert(i-1, j-1));
      if (i > 0 && j < w-1) graph.add_edge(convert(i,j), convert(i-1, j+1));
      if (i < h-1 && j > 0) graph.add_edge(convert(i,j), convert(i+1, j-1));
      if (i < h-1 && j < w-1) graph.add_edge(convert(i,j), convert(i+1, j+1));
      if (i > 0) graph.add_edge(convert(i,j), convert(i-1, j));
      if (j > 0) graph.add_edge(convert(i,j), convert(i, j-1));
      if (i < h-1) graph.add_edge(convert(i,j), convert(i+1, j));
      if (j < w-1) graph.add_edge(convert(i,j), convert(i, j+1));
    }
  }
  cin >> x >> y;

  cout << graph.search(convert(x-1,y-1)) << nl;

  return 0;
}
