#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Edge {
  int id;
  int dist;
  bool add;
  Edge() {}
  Edge(int i, int d, bool a=false): id(i), dist(d), add(a) {}
  ld time(ld k) const {
    return add ? dist + k : dist;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  while (cin >> n >> m) {
    vector<Edge> adj[n+1];

    string s;
    for (int i = 1; i <= n; i++) {
      cin >> s;
      if (s[0] != '?') {
        int dist = stoi(s);
        adj[0].push_back(Edge(i, dist));
        adj[i].push_back(Edge(0, -dist));
      }
      else {
        adj[0].push_back(Edge(i, 1e8));
      }
    }

    int a, b, d;
    for (int i = 0; i < m; i++) {
      cin >> a >> b >> d;
      adj[b].push_back(Edge(a, -d, true));
    }

    double dist[n+1];
    double left, right, mid;
    left = 0;
    right = 2e6;
    while (right - left > EPS) {
      mid = (left + right) / 2;
      fill(dist, dist+n+1, 9e99);

      dist[0] = 0;
      for (int round = 0; round < n; round++) {
        for (int i = 0; i <= n; i++) {
          for (const Edge& e : adj[i]) {
            if (dist[i] + e.time(mid) < dist[e.id]) {
              dist[e.id] = dist[i] + e.time(mid);
            }
          }
        }
      }

      bool neg_cyc = false;
      for (int i = 0; i <= n && !neg_cyc; i++) {
        for (const Edge& e : adj[i]) {
          if (dist[i] + e.time(mid) < dist[e.id] - EPS) {
            neg_cyc = true;
            break;
          }
        }
      }

      if (neg_cyc)
        left = mid;
      else
        right = mid;
    }

    cout << mid << nl;
    for (int i = 1; i <= n; i++) {
      cout << dist[i] << " ";
    }
    cout << nl;
  }

  return 0;
}
