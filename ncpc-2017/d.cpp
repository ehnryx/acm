#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  queue<int> bfs;
  vector<bool> vis(1 << m);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    int u = stoi(s, 0, 2);
    if(!vis[u]) {
      vis[u] = true;
      bfs.push(u);
    }
  }

  int last = 0;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    last = u;
    for(int i=0; i<m; i++) {
      int v = u ^ 1 << i;
      if(!vis[v]) {
        vis[v] = true;
        bfs.push(v);
      }
    }
  }

  for(int i=m-1; i>=0; i--) {
    cout << (last >> i & 1);
  }
  cout << nl;


  return 0;
}
