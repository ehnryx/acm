#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int n, m, k;
int bfs(vector<int> graph[], int s) {
  int res = 0;
  int dist[n+1];
  memset(dist, INF, sizeof(dist));
  queue<int> next;
  next.push(s);
  dist[s] = 0;
  while (!next.empty()) {
    int cur = next.front();
    next.pop();
    res = max(res, dist[cur]);
    for (int neighbour : graph[cur]) {
      if (dist[neighbour] == INF) {
        dist[neighbour] = dist[cur] + 1;
        next.push(neighbour);
      }
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  cin >> n >> m >> k;

  vector<int> graph[n+1];
  
  int a, b;
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, bfs(graph, i));
  }
  cerr << "ans: " << ans << nl;

  if (n - k >= ans) {
    cout << n << nl;
    for (int i = 1; i <= n; i++) {
      cout << i << " ";
    }
    cout << nl;
  }
  else {
    cout << 0 << nl;
  }

  return 0;
}
