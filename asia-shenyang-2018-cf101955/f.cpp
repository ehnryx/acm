#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 1e4+1;
const int W = 1200+1;

int val[N], deg[N], cnt[N];
vector<int> adj[N];

int ans[W];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;

  for (int testnum=1; testnum<=T; testnum++) {
    int n, m, w;
    cin >> n >> m >> w;

    for (int i=1; i<=n; i++) {
      cin >> val[i];
      adj[i].clear();
      deg[i] = 0;
      cnt[i] = 0;
    }

    for (int i=0; i<m; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      deg[b]++;
    }

    queue<int> topo;
    for (int i=1; i<=n; i++) {
      if (deg[i] == 0) {
        topo.push(i);
      }
    }
    while (!topo.empty()) {
    }

    cout << "Case #" << testnum << ": ";
    for(int i=1;i<=3*w; i++) cout << ans[i];
    cout << nl;
  }

  return 0;
}
