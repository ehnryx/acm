#include <bits/stdc++.h>
using namespace std;
#define FILENAME "king"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int N = 1e5+10, K = 20;

int n, m;

vector<int> adj[N];
int in[N], out[N];
int id = 0;

int par[N];
int head[N];
int tail[N];
int parent(int u) {
  return par[u] < 0 ? u: (par[u] = parent(par[u]));
}

int nn;
bool merge(int u, int v) {
  int x = parent(u);
  int y = parent(v);
  tail[x] = tail[y];
  par[y] = x;
  nn--;
  return x == y;
}

bool vis[N];
vector<int> sol;
void dfs(int u) {
  vis[parent(u)] = 1;
  sol.push_back(u);
  /*
  cerr << "dfs " << u << ": ";
  for (int i : sol) cerr << i << " "; cerr << nl;*/
  //u = parent(u);
  if (sol.size() == nn) {
    u = tail[parent(u)];
    for (int v : adj[u]) {
      if (parent(v) == parent(0)) {
        vector<int> ans;
        for (int i : sol) {
          int cur = head[parent(i)];
          while (cur != tail[parent(i)]) {
            ans.push_back(cur);
            cur = adj[cur][0];
          }
          ans.push_back(cur);
        }
        rotate(ans.begin(), find(ans.begin(), ans.end(), 0), ans.end());
        ans.push_back(0);
        for (int i : ans) {
          cout << i+1 << " ";
        }
        cout << nl;
        exit(0);
      }
    }
    sol.pop_back();
    vis[parent(u)] = 0;
    return;
  }
  u = tail[parent(u)];
  for (int i : adj[u]) {
    if (!vis[parent(i)]) {
      dfs(i);
    }
  }
  sol.pop_back();
  vis[parent(u)] = 0;
}

void conn(int u) {
  vis[u] = 1;
  for (int v : adj[u]) {
    if (!vis[v]) conn(v);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
  memset(par, -1, sizeof par);

  cin >> n >> m;
  for(int i=0;i<n;i++) {
    head[i] = tail[i] = i;
  }
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v; u--; v--;
    adj[u].push_back(v);
    in[v]++;
    out[u]++;
  }
  nn = n;
  for (int i = 0; i < n; i++) {
    if (!in[i] || !out[i]) {
      //cerr << "bad " << i << nl;
      puts("There is no route, Karl!");
      return 0;
    }
  }
  conn(0);
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      //cerr << "nconn " << i << nl;
      puts("There is no route, Karl!");
      return 0;
    }
  }
  for (int i = 0; i < n; i++) {
    if (out[i] == 1 && in[i] == 1) {
      int ni = adj[i][0];
      if (out[ni]== 1 && in[ni] ==1) {
        bool b = merge(i, ni);
        if (b) {
          int cur = 0;
          do {
            cout << cur+1 << " ";
            cur = adj[cur][0];
          } while (cur != 0);
          cout << 1 << nl;
          return 0;
        }
      }
    }
  }
  /*
  cerr << nn << nl;
  for (int i = 0; i < n; i++) {
    cerr << i << " -> (" << head[parent(i)] << ", " << tail[parent(i)] << ")\n";
  }*/
  memset(vis, 0, sizeof vis);
  dfs(head[parent(0)]);
  puts("There is no route, Karl!");

  return 0;
}
