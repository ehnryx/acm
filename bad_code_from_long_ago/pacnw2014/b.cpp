#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl endl
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

#define sqr(A) (A)*(A)
struct Circle {
  ll x, y, r;
  int a, b;
  bool contains(const Circle& other) {
    if (sqr(x-other.x) + sqr(y-other.y) < max(sqr(r), sqr(other.r))) {
      return r > other.r;
    }
    else return false;
  }
};

struct Node {
  int id;
  int depth;
  Node(int id = -1, int depth = -1):
    id(id), depth(depth) {}
  bool operator < (const Node& other) const {
    return id < other.id;
  }
};

Circle c[2001];
int depth[2001];
int unadded[2001];
int countdown[2001];
int subcount[2001];
int parent[2001];
set<Node> order;
set<Node> bad;
vector<vector<int>> graph;
vector<vector<int>> subtree;

void add_node(const Node& n) {
  order.insert(n);
  for (int p = parent[n.id]; p != -1; p = parent[p]) {
    subcount[p]++;
  }
}
void erase_node(const Node& n) {
  if (order.count(n)) order.erase(n);
  else bad.erase(n);
  for (int p = parent[n.id]; p != -1; p = parent[p]) {
    subcount[p]--;
  }
  stack<int> next;
  next.push(n.id);
  while (!next.empty()) {
    int cur = next.top();
    next.pop();
    for (int neighbour : graph[cur]) {
      unadded[neighbour]--;
      next.push(neighbour);
    }
  }
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;

  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    graph.clear();
    subtree.clear();
    graph.resize(n);
    subtree.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> c[i].x >> c[i].y >> c[i].r >> c[i].a >> c[i].b;
    }
    queue<int> next;
    for (int i = 0; i < n; i++) {
      subcount[i] = 0;
      int par = -1;
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        if (c[j].contains(c[i])) {
          subtree[j].push_back(i);
          if ((par == -1 || c[j].r < c[par].r))
            par = j;
        }
      }
      if (par == -1) {
        depth[i] = 0;
        next.push(i);
      } else {
        graph[par].push_back(i);
      }
      parent[i] = par;
    }
    while (!next.empty()) {
      int cur = next.front();
      next.pop();
      unadded[cur] = depth[cur];
      for (int neighbour : graph[cur]) {
        depth[neighbour] = 1 + depth[cur];
        next.push(neighbour);
      }
    }

    ll power = 0;
    for (int i = 0; i < n; i++) {
      if (c[i].a == -c[i].b) {
        if (c[i].a == 0) 
          bad.insert(Node(i, -1));
        else if (c[i].a > 0)
          bad.insert(Node(i, 1));
        else 
          bad.insert(Node(i, 0));
        countdown[i] = -1;
      }
      else if (c[i].a >= 0 && c[i].b >= 0) { // both
        power += c[i].a * (depth[i]/2 + depth[i]%2) + c[i].b * (depth[i]/2);
        countdown[i] = 0;
      }
      else if (c[i].a <= 0 && c[i].b >= 0) { // even / none
        if (abs(c[i].a) <= abs(c[i].b)) {
          power += c[i].a * (depth[i]/2) + c[i].b * (depth[i]/2);
          countdown[i] = depth[i]%2;
        } else {
          countdown[i] = depth[i];
        }
      }
      else if (c[i].a >= 0 && c[i].b <= 0) { // one / odd
        if (abs(c[i].a) < abs(c[i].b)) {
          power += c[i].a * (depth[i] > 0);
          countdown[i] = max(0, depth[i]-1);
        }
        else {
          power += c[i].a * (depth[i]/2 + depth[i]%2) + c[i].b * ((depth[i]-1)/2);
          countdown[i] = max(0, (depth[i]-1)%2);
        }
      }
      else { // none
        countdown[i] = depth[i];
      }
      if (countdown[i] == 0) {
        add_node(Node(i, depth[i]));
      }
    }

    vector<int> ans;
    Node curr;
    while (!order.empty() || !bad.empty()) {
      curr.id = INF;
      for (const auto& it : order) {
        if (subcount[it.id] <= 0)
          if (it.id < curr.id)
            curr = it;
      }
      //cerr << nl;
      //cerr << "current: " << curr.id << " " << curr.depth << nl;
      for (const auto& it : bad) {
        //cerr << "bad vis " << it.id << nl;
        //cerr << "subcount " << subcount[it.id] << nl;
        //cerr << "depth: " << it.depth << nl;
        if (subcount[it.id] <= 0) {
          if (it.depth == -1) {
            if (it.id < curr.id)
              curr = it;
          }
          else {
            if (it.id < curr.id && unadded[it.id]%2 == it.depth)
              curr = it;
          }
        }
      }
      if (curr.id == INF) for(;;);
      erase_node(curr);
      ans.push_back(curr.id);
      //cerr << "VISIT " << curr.id+1 << nl;
      for (int sub : subtree[curr.id]) {
        countdown[sub]--;
        if (countdown[sub] == 0) {
          add_node(Node(sub, depth[sub]));
        }
      }
    }

    cout << power << nl;
    for (int it : ans) cout << it+1 << " ";
    cout << nl;
  }

  return 0;
}
