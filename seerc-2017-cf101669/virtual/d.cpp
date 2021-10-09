#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;

const int MAXN = 1e5+10;

int n, m;
vector<int> adj[MAXN];

int vis[MAXN];
int col[MAXN];

void dfs(int u) {
  vis[u] = 1;
  for(int v:adj[u]) {
    if (!vis[v]){
      dfs(v);
    }
  }
}

map<int,int> connect;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> m >> n;
  for(int i=0;i<m;i++) {
    int k; cin >> k;
    for(int j=0;j<k;j++) {
      int a;
      cin >> a;
      if (connect.count(a)) {
        int b = connect[a];
        adj[i].push_back(b);
        adj[b].push_back(i);
      }
      else {
        connect[a] = i;
      }
    }
  }

  int ans = m;
  for(int i=0;i<m;i++) {
    if (!vis[i]) { // true if bipartite
      dfs(i);
      ans--;
    }
  }
  cout << ans <<endl;

  return 0;
}
