#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

const int N = 2e5+7;
vector<int> adj[N];
int indeg[N];
int ans[N/2][2];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, a, b, x, y;
  cin >> n >> a >> b;

  for (int i=0; i<a; i++) {
    cin >> x >> y;
    adj[2*x+1].push_back(2*y);
    indeg[2*y] += 1;
  }

  for (int i=0; i<b; i++) {
    cin >> x >> y;
    adj[2*x].push_back(2*y+1);
    adj[2*y].push_back(2*x+1);
    indeg[2*y+1] += 1;
    indeg[2*x+1] += 1;
  }

  for (int i=1; i<=n; i++) {
    adj[2*i].push_back(2*i+1);
    indeg[2*i+1] += 1;
  }

  splay_tree<splay_node<void, int>> topo;
  for (int i=1; i<=n; i++) {
    for (int j=0; j<2; j++) {
      if (indeg[2*i+j] == 0) {
        //topo.push_back(2*i+j);
        topo.push_front(2*i + j);
      }
    }
  }

  int vis = 0;
  int pos = 0;
  while (!topo.empty()) {
    //int cur = *topo.begin(); topo.pop_front();
    int cur = *topo.rbegin(); topo.pop_back();
    ans[cur/2][cur%2] = pos++;
    vis += 1;

    for (int nxt : adj[cur]) {
      indeg[nxt] -= 1;
      if (indeg[nxt] == 0) {
        // topo.push_back(nxt);
        topo.push_front(nxt);
      }
    }
  }

  if (vis != 2*n) {
    cout << "NO" << nl;
  } else {
    cout << "YES" << nl;
    for (int i=1; i<=n; i++) {
      cout << ans[i][0] << " " << ans[i][1] << nl;
    }
  }

  return 0;
}
