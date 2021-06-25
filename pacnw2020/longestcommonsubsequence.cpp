#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector cnt(m, vector<int>(m));
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < s.size(); j++) {
      for (int k = 0; k < j; k++) {
        cnt[s[k] - 'A'][s[j] - 'A'] += 1;
      }
    }
  }

  vector<vector<int>> adj(m);
  vector<int> deg(m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (cnt[i][j] == n) {
        adj[i].push_back(j);
        deg[j] += 1;
      }
    }
  }

  queue<int> bfs;
  vector<int> dist(m);
  for (int i = 0; i < m; i++) {
    if (deg[i] == 0) {
      bfs.push(i);
      dist[i] = 1;
    }
  }

  while (!empty(bfs)) {
    int u = bfs.front();
    bfs.pop();
    for (int v : adj[u]) {
      dist[v] = max(dist[v], dist[u] + 1);
      if (--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }

  cout << *max_element(begin(dist), end(dist)) << nl;

  return 0;
}
