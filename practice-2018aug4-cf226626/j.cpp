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

struct Node {
  int x, dist;
  Node(){}
  Node(int x, int d): x(x), dist(d) {}
};

const int N = 2e4+1;
int dist[N];

void init() {
  memset(dist, -1, sizeof dist);
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
  init();

  int n, m;
  cin >> n >> m;

  queue<Node> bfs;
  bfs.push(Node(n, 0));
  while (!bfs.empty()) {
    Node cur = bfs.front();
    bfs.pop();
    if (dist[cur.x] != -1) continue;
    dist[cur.x] = cur.dist;

    if (cur.x == m) break;
    if (cur.x-1 > 0) bfs.push(Node(cur.x-1, cur.dist+1));
    if (cur.x*2 < N) bfs.push(Node(cur.x*2, cur.dist+1));
  }

  assert(dist[m] != -1);
  cout << dist[m] << nl;

  return 0;
}
