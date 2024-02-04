#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  int s, t;
  cin >> s >> t;
  auto adj = vector(n + 1, vector<int>());
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  auto colour = vector<int>(n + 1, -1);
  auto find_bad = [&](auto& self, int u, int c) -> bool {
    colour[u] = c;
    for (int v : adj[u]) {
      if (colour[v] == -1) {
        if (self(self, v, c ^ 1)) {
          return true;
        }
      } else if (colour[v] == colour[u]) {
        return true;
      }
    }
    return false;
  };

  if (find_bad(find_bad, s, 0) or colour[s] != colour[t]) {
    cout << "No" << nl;
  } else {
    cout << "Yes" << nl;
  }

  return 0;
}
