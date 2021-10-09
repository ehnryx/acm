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

struct Tree {
  struct Node {
    int cap;
    int sad;
    vector<int> neighbour;
    Node (int c, int germs) {
      cap = c;
      sad = germs;
    }
  };
  vector<Node> g;
  vector<int> roots;
  int build(const vector<vector<int>>& graph, int germs[], int curr, int c) {
    if (graph[curr].size() == 1) {
      return build(graph, graph[curr][0], c+1);
    } 
    else {
      int id = g.size();
      g.push_back(Node(c, germs[curr]));
      for (int neighbour: graph[curr]) {
        g.back().neighbour.push_back(build(graph, neighbour, 0));
      }
      return id;
    }
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  Tree gerg;

  bool troll = true;
  int n, a, b;
  cin >> n;
  int germs[n];
  vector<vector<int>> raw_graph(n);
  
  for (int i = 0; i < n; i++) {
    cin >> germs[i];
    if (germs[i]) 
      troll = false;
  }
  for (int i = 1; i < n; i++) {
    cin >> a >> b;
    raw_graph[a-1].push_back(b-1);
  }

  if (troll) {
    cout << 0 << nl;
  } 
  else {
    int ans = 0;
    gerg.build(raw_graph, germs, 0, 0);
    do {
      ans++;
    } while (gerg.improve())
    cout << ans << nl;
  }

  return 0;
}
