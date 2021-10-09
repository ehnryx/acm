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

struct FordFulkerson {
  int vertices;
  vector<map<int,int>> graph;
  vector<map<int,int>> flow;
  FordFulkerson(int n) {
    vertices = n;
    graph.resize(n);
    flow.resize(n);
  }
  void add_edge(int a, int b, int cap) {
    graph[a][b] += cap;
    graph[b][a] += 0;
    flow[a][b] = flow[b][a] = 0;
  }
  // change dfs to bfs for EdmondsKarp
  int dfs(int s, int t, vector<int>& prev) {
    vector<int> mincap(vertices);
    memset(&mincap[0], INF, vertices*sizeof(mincap[0]));
    memset(&prev[0], -1, vertices*sizeof(prev[0]));

    //stack<int> next;
    queue<int> next;
    next.push(s);
    while (!next.empty()) {
      //int curr = next.top();
      int curr = next.front();
      next.pop();
      if (curr == t) 
        return mincap[t];
      for (pair<int,int> neighbour: graph[curr]) {
        int flo = neighbour.second - flow[curr][neighbour.first];
        if (prev[neighbour.first] == -1 && flo > 0) {
          mincap[neighbour.first] = min(mincap[curr], flo);
          prev[neighbour.first] = curr;
          next.push(neighbour.first);
        }
      }
    }
    return 0;
  }
  int max_flow(int s, int t) {
    int flo = 0;
    for (;;) {
      getchar();
      // find path using dfs
      vector<int> prev(vertices);
      int mincap = dfs(s, t, prev);
      if (mincap == 0)
        break;
      for (int curr = t; curr != s; curr = prev[curr]) {
        flow[prev[curr]][curr] += mincap;
        flow[curr][prev[curr]] -= mincap;
      }
      flo += mincap;
    }
    return flo;
  }
};

struct Dinic {
  int vertices;
  vector<map<int,int>> graph;
  vector<map<int,int>> flow;
  vector<int> level;
  Dinic(int n) {
    vertices = n;
    graph.resize(n);
    flow.resize(n);
    level.resize(n);
  }
  void add_edge(int a, int b, int cap) {
    graph[a][b] += cap;
    graph[b][a] += 0;
    flow[a][b] = flow[b][a] = 0;
  }
  bool bfs(int s, int t) {
    struct Node {
      int index;
      int level;
      Node(int id=-1, int lvl=-1) {
        index = id;
        level = lvl;
      }
      bool operator < (const Node& other) const {
        return other.level < this->level;
      }
    };
    memset(&level[0], -1, vertices*sizeof(level[0]));
    priority_queue<Node> next;
    next.push(Node(s,0));
    Node curr;
    while (!next.empty()) {
      curr = next.top();
      next.pop();
      if (level[curr.index] == -1) {
        level[curr.index] = curr.level;
        if (curr.index == t) 
          return true;
        for (pair<int,int> neighbour: graph[curr.index])
          if (level[neighbour.first] == -1 && flow[curr.index][neighbour.first] < neighbour.second)
            next.push(Node(neighbour.first, curr.level+1));
      }
    }
    return false;
  }
  int dfs(int curr, int t, int f) {
    if (curr == t) 
      return f;
    int flo = 0;
    for (pair<int,int> neighbour: graph[curr]) {
      if (neighbour.second > 0 && level[neighbour.first] == level[curr]+1) {
        int pushed = dfs(neighbour.first, t, min(neighbour.second - flow[curr][neighbour.first], f));
        flow[curr][neighbour.first] += pushed;
        flow[neighbour.first][curr] -= pushed;
        flo += pushed;
        f -= pushed;
      }
    }
    return flo;
  }
  int max_flow(int s, int t) {
    int flo = 0;
    while (bfs(s, t)) {
      flo += dfs(s, t, INF);
    }
    return flo;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int types, n, a, b, temp;
  cin >> types >> n >> a >> b;

  // otherwise
  // find source and sink of graph
  set<int> one, two;
  for (int i = 0; i < a; i++) {
    cin >> temp;
    one.insert(temp);
  }
  for (int i = 0; i < b; i++) {
    cin >> temp;
    two.insert(temp);
  }
  // find sum and build graph
  int sum = 0;
  int pies[n], val[n];
  FordFulkerson graph(types+2);
//  Dinic graph(types+2);
  for (int i = 1; i <= types; i++) {
    if (!two.count(i)) {
      graph.add_edge(0, i, INF);
    }
    else if (!one.count(i)) {
      graph.add_edge(i, types+1, INF);
    }
  }
  for (int i = 0; i < n; i++) {
    cin >> pies[i];
  }
  for (int i = 0; i < n-1; i++) {
    cin >> val[i];
    sum += val[i];
    if (pies[i] != pies[i+1]) {
      graph.add_edge(pies[i], pies[i+1], val[i]);
      graph.add_edge(pies[i+1], pies[i], val[i]);
    }
  }
  int mincut = graph.max_flow(0, types+1);
  cout << sum - mincut << nl;

  return 0;
}
