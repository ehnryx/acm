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

const int N = 1001;
unordered_set<int> succ[N];

struct Node {
  int id, sz;
  Node(){}
  Node(int i, int s): id(i), sz(s) {}
  bool operator < (const Node& n) const {
    return sz < n.sz;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  vector<Node> nodes;
  for (int i = 1; i <= n; i++) {
    int k;
    cin >> k;
    nodes.push_back(Node(i, k));

    int a;
    for (int j = 0; j < k; j++) {
      cin >> a;
      succ[i].insert(a);
    }
  }
  sort(nodes.begin(), nodes.end());

  vector<pii> edges;
  unordered_set<int> roots;
  for (const Node& it : nodes) {
    unordered_set<int> add;
    unordered_set<int> rem;
    for (int r : roots) {
      if (succ[it.id].count(r)) {
        rem.insert(r);
        add.insert(r);
        for (int j : succ[r]) {
          add.insert(j);
        }
      }
    }

    if (add != succ[it.id]) {
      cout << "NO" << nl;
      return 0;
    }
    else {
      for (int r : rem) {
        edges.push_back(pii(it.id, r));
        roots.erase(r);
      }
      roots.insert(it.id);
    }
  }

  if (roots.size() > 1) {
    cout << "NO" << nl;
  } else {
    cout << "YES" << nl;
    for (const pii& e : edges) {
      cout << e.first << " " << e.second << nl;
    }
  }

  return 0;
}
