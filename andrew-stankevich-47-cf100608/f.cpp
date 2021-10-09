#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
  int id, val;
  Node() {}
  Node(int i, int v): id(i), val(v) {}
  bool operator < (const Node& other) const {
    return val < other.val;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  vector<int> taken(n+1, 0);
  vector<int> deg(n+1, 0);
  vector<int> col(n+1, 0);
  vector<int> adj[n+1];

  int a, b;
  for (int i = 1; i < n; i++) {
    cin >> a >> b;
    deg[a]++;
    deg[b]++;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  priority_queue<Node> todo;
  todo.push(Node(1,0));
  while (!todo.empty()) {
    Node cur = todo.top();
    todo.pop();
    cerr << "try " << cur.id << endl;
    if (col[cur.id] != 0) {
      continue;
    }
    cerr << "uncoloured" << endl;

    bitset<5> neighbour;
    for (int x : adj[cur.id]) {
      neighbour[col[x]] = true;
      taken[x]++;
      if (col[x] == 0) {
        if (deg[x] >= 4) todo.push(Node(x, taken[x]));
        else todo.push(Node(x, -1));
      }
    }
    for (int i = 1; i <= 4; i++) {
      if (neighbour[i] == false) {
        col[cur.id] = i;
      }
    }
    cout << cur.id << " " << col[cur.id] << endl;

    cin >> a >> b;
    if (a == -1) {
      return 0;
    }
    col[a] = b;
    for (int x : adj[a]) {
      taken[x]++;
      if (col[x] == 0) {
        if (deg[x] >= 4) todo.push(Node(x, taken[x]));
        else todo.push(Node(x, -1));
      }
    }
  }

  cin >> a >> b;

  return 0;
}
